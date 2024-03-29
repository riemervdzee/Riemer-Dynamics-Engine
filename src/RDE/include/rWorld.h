/*
  RDE/includes/rWorld.h -- World class

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

#ifndef R_WORLD_H_
#define R_WORLD_H_

#include "rSettings.h"
#include "types/rVector.h"
#include "types/rMatrix.h"
#include "rBody.h"
#include "rColinfo.h"
#include <vector>

class rWorld {
private:
	// Holds the "state" of the simulation, containing all bodies etc.
	std::vector <rBody*> StateArray;

	// CollisionVector
	std::vector <rColinfo> CollisionArray;

	// Gravity pull added to each body
	rVector Gravity;
public:
	// Constructor de-constructor
	inline	rWorld( rVector grav): Gravity(grav){}
	~rWorld();

	// Functions for adding and removing bodies
	void	Add		( rBody& body);
	void	Remove	( rBody& body);

	// Move the simulation forward in time by amount dt
	void	CollideAndStep( rReal dt);

	// Based on settings, save the collision points
#ifdef R_SAVE_COLLISIONPOINTS
	std::vector <rVector> CollisionPoints;
#endif

};


#endif /* R_WORLD_H__ */
