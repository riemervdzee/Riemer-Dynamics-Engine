/*
  RDE/src/rBody.cpp -- Body class

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
using namespace std;

/*
 * Calculates mass and inertia from the vertices attached to this body.
 */
rBody::rBody( rGeometry &geom, rMaterial &mat)
	: AngVelocity( 0), Force_A( 0), Geom( &geom), Mat ( &mat)
{
	// Make room for a local copy of the geometry
	Mesh	   = new rVector[ geom.getNum()];
	MeshNum	   = geom.getNum();

	// Vectors of geometry
	rVector *A = geom.getVertices();

	// If density is infinite (0)
	if( Mat->getDensity() == 0)
	{
		// Put everything on 0
		Mass = Inertia = InvMass = InvInertia = 0;
	}
	// If amount of vertices is lower than 3
	else if ( MeshNum < 3)
	{
		// Some basic values
		Mass    = 5.0f * mat.getDensity();
		InvMass = 1 / Mass;
		Inertia = InvInertia = 0;
	}
	// Otherwise calculate it
	else
	{
		// denom = denominator for Inertia
		// numer = numerator for Inertia and used for the Mass (area)
		rReal denom = 0.0f;
		rReal numer = 0.0f;

		// Go through the vertices, and calculate the Cross and Dot products
		// This is required to get the total area and rotation-resistance
		for( int j = MeshNum-1, i = 0; i < MeshNum; j = i, i++)
		{
			// The vectors
			rVector P0 = A[ j];
			rVector P1 = A[ i];

			// Cross product and DOT
			rReal a = fabs( P0.Cross( P1));
			rReal b = P1.Dot( P1) + P1.Dot( P0) + P0.Dot( P0);

			// Add to denom/numer
			denom += a * b;
			numer += a;
		}

		// Obtain the mass and inertia from the calculations made above
		Mass    = numer * mat.getDensity() * 0.5f;
		Inertia = (Mass / 6.0f) * (denom / numer);

		// Get inverse of masses and inertia
		InvMass		= 1/Mass;
		InvInertia	= 1/Inertia;
	}
}

/**
 * Clean up
 */
rBody::~rBody()
{
	delete[] Mesh;
}

/**
 * Calculate mesh
 */
void rBody::CalculateMesh()
{
	// Temp pointers instead of pointers given by functions
	rVector *Vertices	= Geom->getVertices();

	// Convert geom1 vertices to world space
	for( int i = 0; i < MeshNum; i++)
		Mesh[i] = Orientation.Rotate( Vertices[i]) + Position;
}

/**
 * Calculate mesh, just adds an extra offset to the mesh (translations etc.) is faster
 */
void rBody::CalculateMeshTranslation( rVector offset)
{
	// Convert geom1 vertices to world space
	for( int i = 0; i < MeshNum; i++)
		Mesh[i] += offset;
}

/*
 * Euler stepping code to update the body
 */
void rBody::Step( rReal dt, rVector Gravity)
{
	Position += LinVelocity * dt;

	rReal c = cos( AngVelocity * dt);
	rReal s = sin( AngVelocity * dt);
	Orientation *= rMatrix( c, s);

	Orientation.Normalize();

	//Gravity pull
	if( InvMass > 0)
	{
		LinVelocity += Gravity * dt;
	}

	//
	/*rReal sign = (AngVelocity < 0) ? -1 : 1;
	rReal A    = fabs(AngVelocity);

	//Wrapping AngVelocity
	while( AngVelocity >  M_PI) AngVelocity -= M_PI*2;
	while( AngVelocity < -M_PI) AngVelocity += M_PI*2;

	//Bleeding off LinVelocity
	rReal L = LinVelocity.Length();
	if(L > EPSILON)
		LinVelocity.setLength( L - 0.0001);
	else
		LinVelocity = pVector();

	//Bleeding off AngVelocity
	if(A > EPSILON)
		AngVelocity = (A - 0.001) * sign;
	else
		A = 0;*/
}
