/*
  RDE/src/rColinfo.h -- Saves all collisionpoints

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

#ifndef R_COLINFO_H_
#define R_COLINFO_H_

#include "../include/types/rVector.h"
#include "../include/rBody.h"

class rColinfo
{
private:
	rBody	*geom1, *geom2;
public:

	rVector	Force;
	rReal	Depth;

	rBody* getGeom1() const {return geom1;}
	rBody* getGeom2() const {return geom2;}

	rColinfo(): geom1( NULL), geom2( NULL){};
	rColinfo( rBody* _geom1, rBody* _geom2): geom1(_geom1), geom2(_geom2){};
	rColinfo( rBody* _geom1, rBody* _geom2, rVector _Force): geom1(_geom1), geom2(_geom2), Force(_Force){};
};

//Prototypes
bool Collide( rColinfo &CollisionInfo);
rVector CollisionPoint( const rColinfo &CollisionInfo);
void ProcessCollisionPoint( rBody* A, rBody* B, const rVector &P, rVector N, rReal dt);

#endif /* R_COLINFO_H_ */
