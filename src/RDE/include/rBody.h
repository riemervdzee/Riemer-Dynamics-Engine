/*
  RDE/includes/rBody.h -- Body class

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

#ifndef R_BODY_H_
#define R_BODY_H_

#include "types/rVector.h"
#include "types/rMatrix.h"
#include "rGeometry.h"
#include "rMaterial.h"

class rBody
{
public:
	// Constant body values
	rReal		Mass;
	rReal		Inertia;
	rReal		InvMass;
	rReal		InvInertia;

	// State body values
	rVector		Position;
	rMatrix		Orientation;
	rVector		LinVelocity;
	rReal		AngVelocity;

	// Force values, translation LinVel, AngVel
	rVector		Force_T;
	rVector		Force_L;
	rReal		Force_A;

	// Geometry properties
	rGeometry*	Geom;
	rMaterial*	Mat;

	// A local copy of the Geom obj in world-space,
	// translated and rotated according to obj properties
	rVector*	Mesh;
	int			MeshNum;

	// Constructor and deconstructor
	rBody( rGeometry &Geom, rMaterial &Mat);
	~rBody();

	// Stepper function
	void Step( rReal dt, rVector Gravity);

	// Recalculate mesh
	void CalculateMesh();

	// Calculate mesh, just adds an extra offset to the mesh (translations etc.) is faster
	void CalculateMeshTranslation( rVector offset);
};

#endif /* R_BODY_H_ */
