/*
  RDE/src/rBody.cpp -- Get basic collision

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

//We are currently in debug mode, so allow asserts
//#define NDEBUG
#include <assert.h>
using namespace std;

//Prototypes
bool separatedByAxis(const rVector&, rColinfo&, rReal&, const rVector*, const int, const rVector*, const int);

/*
 * Let the 2 geometries given in the pColinfo collide with each other and returns true when there is a collision.
 * Push vector is stored in the pColinfo given as variable
 */
bool Collide( rColinfo &CollisionInfo)
{
	//
	rReal Depth = FLT_MAX;

	//Get the amount of vertices per geomCollisionInfo.getBody1()
	int num1 = CollisionInfo.getBody1()->Geom->getNum();
	int num2 = CollisionInfo.getBody2()->Geom->getNum();

	//Calculate the to be tested axis. If the geom has 4 sides, we only have to test 2 of them
	int numa, numb;
	if(num1 % 2 == 0)numa = num1/2; else numa = num1;
	if(num2 % 2 == 0)numb = num2/2; else numb = num2;

	// Get meshes of both Bodies
	rVector *VerticesGeom1 = CollisionInfo.getBody1()->Mesh;
	rVector *VerticesGeom2 = CollisionInfo.getBody2()->Mesh;

	//Create axis array
	rVector *axis = new rVector[numa+numb];
	int ii = 0;

	//Create axis array for geom1
	for(int j = num1 -1, i = 0; i < numa; j = i, i++, ii++)
	{
		//Create axis
		rVector edg	= VerticesGeom1[j] - VerticesGeom1[i];
		axis[ii] 	= edg.Perpendicular();

		//Normalize axis
		axis[ii].Normalize();
	}

	//Create axis array for geom2
	for(int j = num2 -1, i = 0; i < numb; j = i, i++, ii++)
	{
		//Create axis
		rVector edg	= VerticesGeom2[j] - VerticesGeom2[i];
		axis[ii] 	= edg.Perpendicular();

		//Normalize axis
		axis[ii].Normalize();
	}

	//Set the return value (modified later by seperatedByAxis function)
	bool ret = true;

	//For loop to loop through the to be tested axis
	for(int i = 0; i < ii; i++)
	{
		//Call seperatedByAxis function
		if(separatedByAxis(axis[i], CollisionInfo, Depth, VerticesGeom1, num1, VerticesGeom2, num2))
		{
			//Quit loop and modify the return value
			ret = false;
			break;
		}
	}

	//Save Depth
	CollisionInfo.Depth = Depth;

	//Delete arrays
	delete[] axis;

	//return ret
	return ret;
}

/*
 * Tests if the axis seperates the 2 geoms. These 2 geoms are given by the Vertices1 and Vertices2 pointers.
 * Num1 and num2 are the variables which tell how many vertices these geoms have.
 * pColinfo will be modified when there is a collision found where the "push" vector is smaller than the current one
 */
bool separatedByAxis(const rVector& AxisVector, rColinfo& CollisionInfo, rReal& Depth,
					 const rVector* VerticesA, const int numA, const rVector* VerticesB, const int numB)
{
	//Minimal maximal values for geom A and B
	rReal Amin, Amax;
	rReal Bmin, Bmax;

	//Set them to the projection of the first vertice
	Amin = Amax = VerticesA[0].Dot( AxisVector);
	Bmin = Bmax = VerticesB[0].Dot( AxisVector);

	//Loop for geom A, loops through the vertices given by the function (who are supposed to be in world coordinates)
	for(int i = 1; i < numA; i ++)
	{
		//Projection of the current vertex onto the axis
		rReal dot = VerticesA[i].Dot( AxisVector);

		//Check if this value is lesser than the current minimal or larger than the current maximal
		if		(dot < Amin) Amin = dot;
		else if (dot > Amax) Amax = dot;
	}

	//Loop for geom B. Same as above but other geom
	for(int i = 1; i < numB; i ++)
	{
		//Projection of the current vertice onto the axis
		rReal dot = VerticesB[i].Dot( AxisVector);

		//Check if this value is lesser than the current minimal or larger than the current maximal
		if		(dot < Bmin) Bmin = dot;
		else if (dot > Bmax) Bmax = dot;
	}

	//Calculate the two possible overlap ranges.
	rReal d0 = Bmax - Amin;
	rReal d1 = Bmin - Amax;

	//No overlap detected
	if(d0 < 0.0f || d1 > 0.0f) return true;

	//Find the overlap according to the axis vector (scalar)
	rReal overlap = (d0 < -d1)? d0 : d1;

	//Create the overlap in world space (vector instead of scalar) with correct sign
	//After that we turn the 'overlap' value to an absolute scalar (unsigned)
	rVector vec_overlap = AxisVector * overlap;
	overlap = fabs(overlap);

	//Check if this is either the first test or if the found depth is smaller than the current saved one
	if( overlap < Depth)
	{
		//Save information into the CollisionInfo and CollisionInfoTemp objects
		Depth					= overlap;
		CollisionInfo.Force		= vec_overlap;
	}
	return false;
}
