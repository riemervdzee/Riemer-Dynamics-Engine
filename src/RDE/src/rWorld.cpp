/*
  RDE/src/rWorld.cpp -- World class

  Copyright (c) 2011-2012 Riemer van der Zee <riemervdzee@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

     1. The origin of this software must not be misrepresented; you must not
        claim that you wrote the original software. If you use this software
        in a product, an acknowledgment in the product documentation would be
        appreciated but is not required.

     2. Altered source versions must be plainly marked as such, and must not be
        misrepresented as being the original software.

     3. This notice may not be removed or altered from any source
        distribution.
 */

#include "../include/rWorld.h"
#include <algorithm>

/*
 * Deconstructor
 */
rWorld::~rWorld()
{
	StateArray.clear();
}

/*
 * Adds body to the state array
 */
void rWorld::Add (rBody& body)
{
	body.CalculateMesh();
	StateArray.push_back( &body);
}

/*
 * Removes a body from the state array
 */
void rWorld::Remove (rBody& body)
{
	std::remove ( StateArray.begin(), StateArray.end(), &body);
}

/*
 * Function which lets all the bodies added to this world collide with each other, calculates translations impulses.
 * And the end we step all bodies forward in time by dt
 */
void rWorld::CollideAndStep( rReal dt)
{
	// Update bodies
	for(unsigned int i = 0; i < StateArray.size(); i++)
	{
		// If not a static body
		if( StateArray[i]->InvMass > 0)
		{
			// Let the body do a step with the time and current gravity
			StateArray[i]->Step( dt, Gravity);
			StateArray[i]->CalculateMesh();
		}
	}

	// Clear collisions from last time
	CollisionArray.clear();

	// Clear CollisionPoints
#ifdef R_SAVE_COLLISIONPOINTS
	CollisionPoints.clear();
#endif

	// Overlapping Solving Code. Inner loop for how many iterations requested to solve any errors
	for(int iterations = 0; iterations < ERI; iterations++)
	{
		// If we are at the last iteration, save collisions
		// TODO fix this properly. Always add collisions but never duplicate
		bool push = false;
		if (iterations == 0)
			push = true;

		// Two loops to let everybody check with each other
		for( unsigned int i = 0; i < StateArray.size(); i++)
		{
			for( unsigned int j = i+1; j < StateArray.size(); j++)
			{
				// Sum of both bodies INV mass
				rReal MassRatio = StateArray[i]->InvMass + StateArray[j]->InvMass;

				// Check if a body is movable
				if (MassRatio > 0)
				{
					// Create a collision package between the 2 bodies in line to be tested
					rColinfo CollisionInfo( StateArray[i], StateArray[j]);

					// Check if we have a collision by Separating Axis Test, if so store information in the collision package
					if(::Collide( CollisionInfo))
					{
						// Are we overlapping?
						if( CollisionInfo.Depth > EPSILON)
						{
							//Save required translations to solve any errors
							StateArray[i]->Force_T += CollisionInfo.Force * (StateArray[i]->InvMass / MassRatio) * ERP;
							StateArray[j]->Force_T -= CollisionInfo.Force * (StateArray[j]->InvMass / MassRatio) * ERP;
						}

						// Should we push?
						if ( push)
							CollisionArray.push_back( CollisionInfo);
					}
				}
			}
		}

		// Apply any required translations as requested above
		for( unsigned int i = 0; i < StateArray.size(); i++)
		{
			rBody* body = StateArray[i];

			// If there is a
			if( body->Force_T.LengthSquared() > 0)
			{
				body->Position += body->Force_T;
				body->CalculateMeshTranslation( body->Force_T);
				body->Force_T = rVector( 0, 0);
			}
		}
	}

	// Get collision points and process them
	for( unsigned int i = 0; i < CollisionArray.size(); i++)
	{
		// Get collision point
		rVector CollisionPoint = ::CollisionPoint( CollisionArray[i]);

		// Add current collision point to the array
#ifdef R_SAVE_COLLISIONPOINTS
		CollisionPoints.push_back( CollisionPoint);
#endif

		// Process the collisionpoint
		ProcessCollisionPoint(	CollisionArray[i].getBody1(),
								CollisionArray[i].getBody2(),
								CollisionPoint,
								CollisionArray[i].Force,
								dt);
	}
}
