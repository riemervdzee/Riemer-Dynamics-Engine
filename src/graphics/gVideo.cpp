/*
  gVideo.cpp -- Graphics back-end for tutorial purposes

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

#include "gVideo.h"
#include "../RDE/include/types/rVector.h"
#include <GL/gl.h>
using namespace std;

/*
 * Draws a pixel
 */
void drawPixel( float x, float y)
{
	glColor3f( 1, 0, 0);
	glPointSize( 2.0);

	glBegin( GL_POINTS);
		glVertex2f( x, y);
	glEnd();
}

/*
 * Draws a line
 */
void drawLine( float x0, float y0, float x1, float y1)
{
	glColor3f( 1, 0, 0);
	glBegin(GL_LINES);
		glVertex2f( x0, y0);
		glVertex2f( x1, y1);
	glEnd();

}

/*
 * Draws a geometry at the correct place
 */
void drawGeom ( rBody &body)
{
	glLoadIdentity();

	// Vertices
	rVector	*V	= body.Mesh;
	int		 N	= body.MeshNum;

	//Initialize color and start drawing
	glColor3f( 0.92, 0.97, 0.35);
	glBegin( GL_TRIANGLE_FAN);

	// Start with middle and last
	glVertex2f( body.Position.getX(), body.Position.getY());
	glVertex2f( V[N-1].getX(), V[N-1].getY());

	//Loop through the vertices
	for(int i = 0; i < N; ++i)
	{
		glVertex2f( V[i].getX(), V[i].getY());
	}

	//End drawing
	glEnd();
}

