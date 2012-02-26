/*
  RDE/src/CollisionPoint.cpp -- Finds the collisionpoint of a collision

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

#include "../include/types/rVector.h"
#include "../include/types/rMatrix.h"
#include "../include/rColinfo.h"
#include <float.h>

/**
 * Find collision point
 */
rVector CollisionPoint( const rColinfo &CollisionInfo)
{
	//
	int numA = CollisionInfo.getBody1()->Geom->getNum();
	int numB = CollisionInfo.getBody2()->Geom->getNum();

	//Temp pointers instead of pointers given by functions, limits chances that variables are getting reloaded -> hopefully faster execution
	//rMatrix OrientA = CollisionInfo.getBody1()->Orientation;
	//rMatrix OrientB = CollisionInfo.getBody2()->Orientation;
	rVector *VertA	= CollisionInfo.getBody1()->Mesh;
	rVector *VertB	= CollisionInfo.getBody2()->Mesh;
	rVector PosA	= CollisionInfo.getBody1()->Position;
	rVector PosB	= CollisionInfo.getBody2()->Position;

	//Normalize the Force vector
	rVector Normal	= CollisionInfo.Force;
	Normal.Normalize();

	//We use -FLT_MAX, as for some reason FLT_MIN is making the simulation bugged
	rReal A1 =  FLT_MAX, A2 =  FLT_MAX;
	rReal B1 = -FLT_MAX, B2 = -FLT_MAX;

	//Begin positions
	int A1pos = -1, A2pos = -1;
	int B1pos = -1, B2pos = -1;


	//Loop for geom A, loops through the vertices given by the function (who are supposed to be in world coordinates)
	for(int i = 0; i < numA; i ++)
	{
		//Projection of the current vertex onto the axis
		rReal dot = VertA[i].Dot( Normal);

		//Get the two smallest quantities laying on the axis of this body
		if (dot < A1)
		{
			A2		= A1;
			A2pos	= A1pos;
			A1		= dot;
			A1pos	= i;
		}
		else if (dot < A2)
		{
			A2		= dot;
			A2pos	= i;
		}
	}

	//Loop for geom B, loops through the vertices given by the function (who are supposed to be in world coordinates)
	for(int i = 0; i < numB; i ++)
	{
		//Projection of the current vertex onto the axis
		rReal dot = VertB[i].Dot( Normal);

		//Get the two largest quantities laying on the axis of this body
		if (dot > B1)
		{
			B2		= B1;
			B2pos	= B1pos;
			B1		= dot;
			B1pos	= i;
		}
		else if (dot > B2)
		{
			B2		= dot;
			B2pos	= i;
		}
	}

	//Vector to be returned
	rVector ret;

	//Overlap vectors
	rVector overlap = (fabs(B1 - A1) * 0.5) * Normal;

	//Check if A is colliding with an Edge
	if ( A1 + 0.5 > A2 && A1 - 0.5 < A2)
	{
		//Check if B is colliding with an Edge
		if ( B1 + 0.5 > B2 && B1 - 0.5 < B2)
		{
			//This is an Edge-Edge collision, do some magic stuff
			rVector vec[4];
			vec[0] = VertA[A1pos] + overlap;
			vec[1] = VertA[A2pos] + overlap;
			vec[2] = VertB[B1pos] - overlap;
			vec[3] = VertB[B2pos] - overlap;

			//Find the middle vector
			rVector Middle;
			Middle = PosA + ((PosB - PosA) * 0.5);

			//Positions relative to the middle
			rVector p[4];
			p[0] = Middle - vec[0];
			p[1] = Middle - vec[1];
			p[2] = Middle - vec[2];
			p[3] = Middle - vec[3];

			//Dot products
			rReal f[4];
			f[0] = p[0].Dot(p[0]);
			f[1] = p[1].Dot(p[1]);
			f[2] = p[2].Dot(p[2]);
			f[3] = p[3].Dot(p[3]);

			//Begin positions for the upcomming statements
			rReal min1 = FLT_MAX, min2 = FLT_MAX;
			int min1pos = -1, min2pos = -1;

			//Find the two nearest points to the middle
			for(int i = 0; i < 4; i++)
			{
				if( f[i] < min1)
				{
					min2	= min1;
					min2pos	= min1pos;
					min1	= f[i];
					min1pos	= i;
				}
				else if( f[i] < min2)
				{
					min2	= f[i];
					min2pos	= i;
				}
			}

			//Find the middle vector between the two nearest points near the middle of the two bodies
			ret = vec[min1pos] + (( vec[min2pos] - vec[min1pos] ) * 0.5);
		}
		else
		{
			//Since B is not colliding with an Edge, simply say that the nearest vertex is the colliding vertex
			ret = VertB[B1pos] - overlap;
		}
	}
	else
	{
		//Since A is not colliding with an Edge, simply say that the nearest vertex is the colliding vertex
		ret = VertA[A1pos] + overlap;
	}

	return ret;
}
