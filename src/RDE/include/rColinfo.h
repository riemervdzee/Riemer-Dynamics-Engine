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
	rBody	*body1, *body2;
public:

	rVector	Force;
	rReal	Depth;

	// Return bodies
	rBody* getBody1() const { return body1;}
	rBody* getBody2() const { return body2;}

	rColinfo(): body1( NULL), body2( NULL), Depth(0){};
	rColinfo( rBody* _body1, rBody* _body2): body1(_body1), body2(_body2), Depth(0){};
	rColinfo( rBody* _body1, rBody* _body2, rVector _Force): body1(_body1), body2(_body2), Force(_Force){};
};

//Prototypes
bool Collide( rColinfo &CollisionInfo);
rVector CollisionPoint( const rColinfo &CollisionInfo);
void ProcessCollisionPoint( rBody* A, rBody* B, const rVector &P, rVector N, rReal dt);

#endif /* R_COLINFO_H_ */
