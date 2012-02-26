/*
  RDE/includes/rGeom.h -- Geometry object, contains vertice-collision data

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

#ifndef R_GEOMETRY_H_
#define R_GEOMETRY_H_

#include "types/rVector.h"

class rGeometry
{
private:
	//Geometry properties
	rVector*	Vertices;
	int			Num;

public:
	//Constructor, destructor and copy-constructor
	rGeometry(): Vertices(NULL), Num(0){}
	rGeometry( const rGeometry &G);
	~rGeometry();

	//Get functions
	rVector* 	getVertices()	const { return Vertices;}
	int			getNum()		const { return Num;}

	//Creation methods of bodies
	void CreatePolygon	( int Number, rReal Radius);
	void CreateBox		( rReal Width, rReal Height);
};


#endif /* R_GEOMETRY_H_ */
