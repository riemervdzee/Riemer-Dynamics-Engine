/*
  RDE/src/rGeom.cpp -- Geometry object, contains vertice-collision data

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

#include "../include/rGeometry.h"
#include <algorithm>

/*
 * Copy constructor, since we deal with pointers
 */
rGeometry::rGeometry( const rGeometry &G)
	: Num( G.Num), Vertices( new rVector[ G.Num])
{
	std::copy( G.Vertices, G.Vertices + G.Num, Vertices);
}

/*
 * De-constructor, deletes data if we saved any
 */
rGeometry::~rGeometry()
{
	// Only delete Vertices when it contains data
	if( Vertices != NULL)
	{
		delete[] Vertices;
	}
}

/*
 * Function to create a polygon convex Geometry
 */
void rGeometry::CreatePolygon (int Number, rReal Radius)
{
	// StepSize between points (in Radians) and current stepPosition(will be incremented with stepsize every step)
	rReal stepSize	= M_PI * 2 / Number;
	rReal stepPos	= 0;

	// Create vector array and set VerticeData to true
	Vertices	= new rVector[Number];
	Num			= Number;

	// Calculate positions
	for( int i = 0; i < Number; i++, stepPos += stepSize)
	{
		// Calculate sinus and cosinus of the current step
		rReal c = cos( stepPos) * Radius;
		rReal s = sin( stepPos) * Radius;

		//Save position in Vertices list
		Vertices[i].setX(c);
		Vertices[i].setY(s);
	}
}

/*
 * Function to create a box
 */
void rGeometry::CreateBox (rReal Width, rReal Height)
{
	// Create vector array and set VerticeData to true
	Vertices	= new rVector[4];
	Num			= 4;

	// half the width and height values
	Width  /= 2;
	Height /= 2;

	// Create Vertices list
	Vertices[0] = rVector(  Width, -Height);
	Vertices[1] = rVector(  Width,  Height);
	Vertices[2] = rVector( -Width,  Height);
	Vertices[3] = rVector( -Width, -Height);
}
