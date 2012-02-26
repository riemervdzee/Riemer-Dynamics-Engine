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


//Prototypes
rReal CalculateMass   (const rVector* A, int Anum, rReal density);
rReal CalculateInertia(const rVector* A, int Anum, rReal mass);

/*
 * Calculates mass and intertia from the vertices attached to this body.
 */
rBody::rBody( rGeometry &geom, rMaterial &mat): AngVelocity(0), Force_A(0)
{
	// Assign variables
	Geom = &geom;
	Mat  = &mat;

	//
	Mesh	= new rVector[ geom.getNum()];
	MeshNum	= geom.getNum();

	if(Mat->getDensity() == 0)
	{
		Mass = Inertia = InvMass = InvInertia = 0;
	}
	else
	{
		Mass	= CalculateMass(	Geom->getVertices(), Geom->getNum(), Mat->getDensity());
		Inertia	= CalculateInertia(	Geom->getVertices(), Geom->getNum(), Mass);

		InvMass		= 1/Mass;
		InvInertia	= 1/Inertia;
	}
}

/**
 * Cleans up
 */
rBody::~rBody()
{
	// Only delete Vertices when it contains data
	if( Mesh != NULL)
	{
		delete[] Mesh;
	}
}

/**
 * Calculate mesh
 */
void rBody::CalculateMesh()
{
	// Temp pointers instead of pointers given by functions
	rVector *Vertices	= Geom->getVertices();

	// Convert geom1 vertices to world space
	for(int i = 0; i < MeshNum; i++)
		Mesh[i] = Orientation.Rotate( Vertices[i]) + Position;
}

/*
 * Euler stepping code to update the body
 */
void rBody::Step( rReal dt, rVector Gravity)
{
	Position += LinVelocity*dt;

	rReal c = cos(AngVelocity*dt);
	rReal s = sin(AngVelocity*dt);
	Orientation *= rMatrix(c, s);

	Orientation.Normalize();

	//Gravity pull
	if(InvMass > 0)
	{
		LinVelocity+= Gravity * dt;
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

// taken from
// http://www.physicsforums.com/showthread.php?s=e251fddad79b926d003e2d4154799c14&t=25293&page=2&pp=15
// TODO rewrite!!
rReal CalculateMass(const rVector* A, int Anum, rReal density)
{
	if (Anum < 2)
		return 5.0f * density;

	rReal mass = 0.0f;

	for(int j = Anum-1, i = 0; i < Anum; j = i, i ++)
	{
		rVector P0 = A[j];
		rVector P1 = A[i];
#ifdef REAL_DOUBLE
		mass +=  fabs( P0.Cross(P1));
#else
		mass +=  (float) fabs( P0.Cross(P1));
#endif
	}
	if (Anum <= 2)
		mass = 10.0f;

	mass *= density * 0.5f;

	return mass;
}

// taken from
// http://www.physicsforums.com/showthread.php?s=e251fddad79b926d003e2d4154799c14&t=25293&page=2&pp=15
rReal CalculateInertia(const rVector* A, int Anum, rReal mass)
{
	if (Anum == 1)	return 0.0f;

	rReal denom = 0.0f;
	rReal numer = 0.0f;

	for(int j = Anum-1, i = 0; i < Anum; j = i, i ++)
	{
		rVector P0 = A[j];
		rVector P1 = A[i];

#ifdef REAL_DOUBLE
		rReal a = fabs(P0.Cross(P1));
#else
		rReal a = (float) fabs(P0.Cross(P1));
#endif
		rReal b = (P1.Dot(P1) + P1.Dot(P0) + P0.Dot(P0));

		denom += (a * b);
		numer += a;
	}
	rReal inertia = (mass / 6.0f) * (denom / numer);

	return inertia;
}
