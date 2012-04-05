/*
  RDE/src/rDynamics.cpp -- Impulse solver

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

#include "../include/rSettings.h"
#include "../include/rBody.h"

#include <iostream>
using namespace std;

/*
 * Creates an impulse from the contact position with both bodies velocities (both angular and linear).
 * Adds some elasticity in the mix and hopefully we will implement kinetic friction as well soon.
 * After that the impulse is applied on both bodies to change their velocities (both angular and linear again).
 */
void ProcessCollisionPoint( rBody* A, rBody* B, const rVector &P, rVector N, rReal dt)
{
	// If normal is screwed up, return
	// if( N.Dot(N) < EPSILON)return;

	// Material properties.
	//   e = Elasticity, the jumpy-niss of objects when colliding
	//   r = resistance, the drag when 2 bodies are touching.
	//TODO use materials of the objects
	rReal e = 0.4;
	rReal u = 0.4;

	// Normalize the normal
	N.Normalize();

	// Get Tangent
	rVector T = N;
	T.Perpendicular();

	// Position P relative to the bodies
	rVector pA = P - A->Position;
	rVector pB = P - B->Position;

	// Rotation vector, who are perpendicular versions of pA and pB
	rVector aA = pA;
	rVector aB = pB;
	aA.Perpendicular();
	aB.Perpendicular();

	// Velocities
	rVector vA = A->LinVelocity + aA * A->AngVelocity;
	rVector vB = B->LinVelocity + aB * B->AngVelocity;
	rVector v  = vA - vB;

	// Get velocities along the Normal and Tangent
	rReal	vN = N.Dot( v);
	rReal	vT = T.Dot( v);

	// Pre-calculation, saves us some time.
	rReal	kA = pA.Cross( N);
	rReal	kB = pB.Cross( N);
	rReal	uA = A->InvInertia * kA;
	rReal	uB = B->InvInertia * kB;

	// Denominator
	rReal	Denom = A->InvMass + B->InvMass + (kA * uA) + (kB * uB);

	// Impulse calculation
	rReal	iNumer = -(1 + e) * vN;
	rReal	i = iNumer / Denom;

	// Friction
	rReal	fNumer = u * vN;
	rReal	f = fNumer / Denom;

	// If i is positive, otherwise the bodies are moving from each other / sliding
	if ( i > EPSILON)
	{
		//The impulse
		rVector impulse  = N * i;

		//Apply impulses to bodies velocities
		A->LinVelocity += impulse * A->InvMass;
		B->LinVelocity -= impulse * B->InvMass;
		A->AngVelocity += i * uA;
		B->AngVelocity -= i * uB;
	}

	// Implement friction
	if ( fabs(vT) > EPSILON && fabs(f) > EPSILON)
	{
		// Friction vector
		// TODO don't make this one larger than vT
		rVector Friction  = T * f;

		//
		if ( vT < 0.0)
			Friction = -Friction;

		//Apply impulses to bodies velocities
		A->LinVelocity += Friction * A->InvMass;
		B->LinVelocity -= Friction * B->InvMass;
		A->AngVelocity += f * uA;
		B->AngVelocity -= f * uB;
	}
}
