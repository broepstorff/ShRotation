/*********************************
SH Rotation

Author: John Hable

Date:   June 29, 2014

License:
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
************************************/

#ifndef _VEC3_H_
#define _VEC3_H_

#include <math.h>
#include <stdlib.h>

struct Vec3
{
	Vec3()
	{
		x = y = z = 0.0f;
	}
	
	Vec3(double _x, double _y, double _z)
	{
		x = _x; y = _y; z = _z;
	}
	
	double LengthSqr() const
	{
		return x*x + y*y + z*z;
	}

	void Normalize()
	{
		double lenSqr = LengthSqr();

		// we don't care at all about speed, so just be super safe
		if (lenSqr == 0.0)
		{
			x = 1.0;
			y = 0.0;
			z = 0.0;
		}
		else
		{
			double invScale = 1.0f/sqrt(lenSqr);
			x *= invScale;
			y *= invScale;
			z *= invScale;
		}
	}

	static Vec3 RandomNormal()
	{
		Vec3 ret;
		ret.x = double((rand()%2001)-1000);
		ret.y = double((rand()%2001)-1000);
		ret.z = double((rand()%2001)-1000);

		ret.Normalize();
		return ret;
	}

	static Vec3 FromPtr(const double data[3])
	{
		Vec3 ret;
		ret.x = data[0];
		ret.y = data[1];
		ret.z = data[2];
		return ret;
	}

	double x, y, z;
};



#endif
