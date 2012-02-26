/*
  RPE/includes/types/rVector.h -- Standard vector class for RPE

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
        appreciated but iIk vind de conclusie; 'Omdat ze er niet meer kan ze ook geen Ereburger meer worden', maar erg raar. Moeten we ook Ereburger gaan intrekken nu de personen overleden zijn die het in het verleden waren? Dat is toch ook totaal niet nodig? Ondanks dat ze overleden is, moet het wel mogelijk zijn om haar Ereburgerschap te geven. Dat is wel passend na velen jaren inzet voor het Graafschap.s not required.

     2. Altered source versions must be plainly marked as such, and must not be
        misrepresented as being the original software.

     3. This notice may not be removed or altered from any source
        distribution.
 */

#ifndef R_VECTOR_H_
#define R_VECTOR_H_

#include <math.h>
#include <stdio.h>
#include "../rSettings.h"

class rVector
{
private:
	// Variables representing the vector
	rReal x, y;

public:
	// Constructors
	inline rVector(): x(0), y(0){}
	inline rVector( rReal _x,rReal _y): x(_x), y(_y){}

	// Get commands
	inline rReal getX() const {return x;}
	inline rReal getY() const {return y;}

	// Set commands
	inline rVector& setX( rReal _x) {x = _x; return *this;}
	inline rVector& setY( rReal _y) {y = _y; return *this;}

	// Vector adding/subtracting
	inline rVector  operator  + (const rVector &A) const {return rVector( x + A.x, y + A.y);}
	inline rVector  operator  - (const rVector &A) const {return rVector( x - A.x, y - A.y);}
	inline rVector  operator  * (const rReal s)    const {return rVector( x * s, y * s);}
	inline rVector  operator  / (const rReal s)    const {return rVector( x / s, y / s);}


	// Scalar multiplication/dividing
	inline rVector& operator += (const rVector &A) {x += A.x; y += A.y; return *this;}
	inline rVector& operator -= (const rVector &A) {x -= A.x; y -= A.y; return *this;}
	inline rVector& operator *= (const rReal s)    {x *= s; y *= s; return *this;}
	inline rVector& operator /= (const rReal s)    {x /= s; y /= s; return *this;}

	// Changes the sign of a vector
	inline rVector  operator -(void) const {return rVector(-x, -y); }

	// Multiplies with a scalar, so we can write s * rVector where s is the scalar
	friend rVector operator * (rReal s, const rVector& A) { return rVector(A.x*s, A.y*s); }

	// Cross product
	inline rReal Cross (const rVector &A) const { return (x * A.y) - (y * A.x); }

	// Dot product
	inline rReal Dot (const rVector &A) const { return (x*A.x) + (y*A.y); }

	// Return length
	inline rReal Length(void) const {return (rReal) sqrt(x*x + y*y); }

	// Normalize
	rVector& setLength( rReal len)
	{
		// Limit to only one devision
		rReal L = len / Length();

		// Multiply X and Y with L
		x *= L;
		y *= L;

		// Return ourself
		return *this;
	}

	// Normalize
	rVector& Normalize(void)
	{
		// Limit to only one devision
		rReal L = 1.0f / Length();

		// Multiply X and Y with L
		x *= L;
		y *= L;

		// Return ourself
		return *this;
	}

	// Makes this vector perpendicular to the existing one (rotating 90 degrees right-hand wise)
	rVector& Perpendicular(void)
	{
		rReal temp = x;
		x = -y;
		y = temp;

		//Return ourself
		return *this;
	}

	//Clamp vector to rectangle formed by min/max
	rVector& Clamp(const rVector& min, const rVector& max)
	{
		// Clamp X
		x = (x > max.x) ? max.x : (x < min.x) ? min.x : x;

		// Clamp Y
		y = (y > max.y) ? max.y : (y < min.y) ? min.y : y;

		//Return ourself
		return *this;
	}
};


#endif /* R_VECTOR_H_ */
