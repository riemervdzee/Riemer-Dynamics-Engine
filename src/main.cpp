/*
  main.cpp -- Main entry of program. Sets up logics and is controller-like

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

#include <SDL/SDL.h>
#include <string>
#include "RDE/include/rde.h"
#include "graphics/graphics.h"
using namespace std;

// Create world
rWorld World( rVector( 0, -125));

/*rWorld World( rVector( 0, -125));
rGeometry GeomWorld1, GeomWorld2, GeomMain, GeomBlocks, GeomBlocks2;
rBody BodyWorld1, BodyWorld2, BodyWorld3, BodyWorld4, BodyMain;
rBody Body1, Body2, Body3, Body4, Body5, Body6;*/

/*
 * todo: actually use these..
void init() {

}

void update() {

}*/

void draw() {
	// Set red color
	drawSetColor( gRED);

	// Draw collision points
	for( unsigned int i = 0; i < World.CollisionPoints.size(); ++i)
	{
		rVector v = World.CollisionPoints.at( i);
		drawPixel( v.getX(), v.getY());
	}
}

/*
 * Main Entry: added the Argc and Argv variables as arguments as SDL wants it that way
 */
int main( int argc, char **argv )
{
	// Display something fun
	string caption = string( "Physics ") + VERSION_FULL + " - By Riemer van der Zee";

	// Create a window
	if( window_create( caption.c_str() ))
		exit (0);

	// Create geometries
	rGeometry GeomWorld1, GeomWorld2, GeomMain, GeomBlocks, GeomBlocks2;
	GeomWorld1 .CreateBox( 800,     4);
	GeomWorld2 .CreateBox(   4, 591.5);
	GeomBlocks .CreateBox( 120,   120);
	GeomMain   .CreatePolygon( 5, 100);

	// Materials. first is world-material, they are infinite-heavy = 0
	rMaterial matWorld  ( 0, 0.8);
	rMaterial matNormal ( 5, 0.8);

	// Create bodies
	rBody BodyWorld1( GeomWorld1, matWorld);
	rBody BodyWorld2( GeomWorld1, matWorld);
	rBody BodyWorld3( GeomWorld2, matWorld);
	rBody BodyWorld4( GeomWorld2, matWorld);
	rBody BodyMain  ( GeomMain  , matNormal);
	rBody Body1     ( GeomBlocks, matNormal);
	rBody Body2     ( GeomBlocks, matNormal);
	rBody Body3     ( GeomBlocks, matNormal);
	rBody Body4     ( GeomBlocks, matNormal);
	rBody Body5     ( GeomBlocks, matNormal);
	rBody Body6     ( GeomBlocks, matNormal);

	// Body Positions
	BodyWorld1.Position = rVector ( 400,   2);
	BodyWorld2.Position = rVector ( 400, 598);
	BodyWorld3.Position = rVector (   2, 300);
	BodyWorld4.Position = rVector ( 798, 300);
	BodyMain  .Position = rVector ( 410, 220);
	Body1     .Position = rVector ( 250, 350);
	Body2     .Position = rVector ( 250, 250);
	Body3     .Position = rVector ( 250, 150);
	Body4     .Position = rVector ( 570, 350);
	Body5     .Position = rVector ( 570, 250);
	Body6     .Position = rVector ( 570, 150);
	BodyMain  .Orientation.setAngle(18);

	// Add bodies to the world
	World.Add( BodyWorld1);
	World.Add( BodyWorld2);
	World.Add( BodyWorld3);
	World.Add( BodyWorld4);
	World.Add( BodyMain);
	World.Add( Body1);
	World.Add( Body2);
	World.Add( Body3);
	World.Add( Body4);
	World.Add( Body5);
	World.Add( Body6);

	// Initialize
	//init();

	// Step
	while( INPUT_STOP == false)
	{
		// Get all new input-updates
		InputUpdate();

		// Keys
		if(KEY_LEFT	) BodyMain.LinVelocity -= rVector( 6, 0);
		if(KEY_RIGHT) BodyMain.LinVelocity += rVector( 6, 0);
		if(KEY_UP	) BodyMain.LinVelocity += rVector( 0, 9);
		if(KEY_DOWN	) BodyMain.LinVelocity -= rVector( 0, 4);

		// Let the bodies collide
		World.CollideAndStep( 0.01);

		// Draw geoms
		drawSetColor( gLIMEGREEN);
		drawGeom( BodyWorld1);
		drawGeom( BodyWorld2);
		drawGeom( BodyWorld3);
		drawGeom( BodyWorld4);
		drawSetColor( gFIREBRICK);
		drawGeom( BodyMain);
		drawSetColor( gLIMEGREEN);
		drawGeom( Body1);
		drawGeom( Body2);
		drawGeom( Body3);
		drawGeom( Body4);
		drawGeom( Body5);
		drawGeom( Body6);

		// Not used yet
		//update();
		draw();

		// Flip the screen
		window_flip();

		// Wait for some time
		SDL_Delay( 10);
	}

	return 0;
}
