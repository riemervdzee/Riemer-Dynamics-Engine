/*
  RPE/includes/types/rMatrix.h -- Standard matrix class for RPE

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

#ifndef R_MATRIX_H_
#define R_MATRIX_H_

#include <cmath>
#include <cstdio>
#include "../rSettings.h"
#include "rVector.h"

// Some extra math declarations
const rReal RADTODEG = 180 / M_PI;
const rReal DEGTORAD = M_PI / 180;


class rMatrix
{
private:
	// The variables representing the matrix. They are the sinus & cosinus results of the angle
	rReal c, s;

public:
	// Constructors
	inline rMatrix(): c(1), s(0){}
	inline rMatrix( rReal _c,rReal _s): c(_c), s(_s){}

	// Get functions
	inline rReal getC(){ return c;}
	inline rReal getS(){ return s;}

	// Sets the angle
	void setAngle( const rReal angle)
	{
		c = cos( angle * DEGTORAD);
		s = sin( angle * DEGTORAD);
	}

	// Returns the angle
	rReal getAngle() const
	{
		return acos(c)*RADTODEG;
	}

	// Normalize the matrix
	void Normalize()
	{
		rReal L = 1.0f / (sqrt(c*c + s*s));
		c *= L;
		s *= L;
	}

	// Print DEBUG info
	inline void Print() const
	{
		printf("xX: %f xY: %f\n", c, s);
	}

	// Rotates a vector and returns it
	rVector Rotate ( rVector &A) const
	{
		rReal _x = A.getX() * c + A.getY() *-s;
		rReal _y = A.getX() * s + A.getY() * c;

		return rVector( _x, _y);
	}

	// Multiply this matrix with another and return the result
	rMatrix  operator * ( const rMatrix &A) const
	{
		rReal _c = c * A.c + s *-A.s;
		rReal _s = c * A.s + s * A.c;
		return rMatrix( _c, _s);
	}

	// Multiply this matrix with another and put the result in this matrix
	rMatrix &operator *= ( const rMatrix &A)
	{
		rReal _c = c * A.c + s *-A.s;
		rReal _s = c * A.s + s * A.c;
		c = _c;
		s = _s;
		return *this;
	}
};

#endif /* R_MATRIX_H_ */
