/*
  RDE/includes/rMaterial.h -- Includes all properties of a material

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

#ifndef R_MATERIAL_H_
#define R_MATERIAL_H_

#include "rSettings.h"

class rMaterial {
private:
	rReal _density;
	rReal _elasticity;

public:
	rMaterial( rReal density, rReal elasticity) : _density(density), _elasticity(elasticity) {}

	rReal mixElasticity( const rMaterial &mat);
	inline rReal getDensity() const {return _density;}

};


#endif /* R_MATERIAL_H__ */
