/*
  gVideo.h -- Graphics back-end for tutorial purposes

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

#ifndef GRAPH_VIDEO_H_
#define GRAPH_VIDEO_H_

#include "../RDE/include/rBody.h"

void drawPixel    ( float  x, float  y);
void drawLine     ( float x0, float y0, float x1, float y1);
void drawGeom     ( rBody &body);

#endif /* GRAPH_VIDEO_H_*/

