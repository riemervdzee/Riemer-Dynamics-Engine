/*
  RDE/includes/rParameters.h -- Constants which are used in RDE

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

#ifndef R_SETTINGS_H_
#define R_SETTINGS_H_

// Should we use doubles instead of floats?
//#define REAL_DOUBLE

// Should we save the collision points?
#define R_SAVE_COLLISIONPOINTS

// Determine val
#ifdef REAL_DOUBLE
typedef double rReal;
#else
typedef float rReal;
#endif

// Values
const rReal EPSILON	= 0.0001; // Standard used Epsilon value
const rReal ERP		= 0.95;   // Error Reduction Parameter
const int   ERI		= 10;     // Error Reduction Iterations

#endif /* R_SETTINGS_H_ */
