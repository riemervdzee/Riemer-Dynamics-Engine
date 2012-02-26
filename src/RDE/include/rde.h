/*
  RDE/includes/rde.h -- Main include file for the RDE library

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

#ifndef R_DE_H_
#define R_DE_H_

// Version information
#define VERSION_FULL "0.1.0"
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0

// Include basics
#include "rSettings.h"
#include "types/rVector.h"
#include "types/rMatrix.h"

// Include RDE
#include "rGeometry.h"
#include "rMaterial.h"
#include "rBody.h"
#include "rWorld.h"

#endif /* R_DE_H_ */
