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

#include "ShProject.h"


// these were originally made for 32bit floats so there might not be enough digits for 64bit doubles
const static double s_c0 = 0.28209479177; // 1 / (2 * sqrt(pi))
const static double s_c1 = 0.4886025119; // sqrt(3)/(2*sqrt(pi))
const static double s_c2 = 1.09254843059; // sqrt(15)/(2*sqrt(pi))
const static double s_c3 = 0.94617469575; // (3*sqrt(5))/(4*sqrt(pi))
const static double s_c4 = -0.31539156525;// (-sqrt(5))/(4*sqrt(pi))
const static double s_c5 = 0.54627421529; // (sqrt(15))/(4*sqrt(pi))

void ProjectNormalToShBand0(double coef[1], Vec3 N)
{
	coef[0] = s_c0;
}

void ProjectNormalToShBand1(double coef[3], Vec3 N)
{
	coef[0] = -s_c1 * N.y;
	coef[1] = s_c1 * N.z;
	coef[2] = -s_c1 * N.x;
}

void ProjectNormalToShBand2(double coef[5], Vec3 N)
{
	coef[0] = s_c2*N.x*N.y;
	coef[1] = -s_c2*N.y*N.z;
	coef[2] = s_c3*N.z*N.z + s_c4;
	coef[3] = -s_c2*N.x*N.z;
	coef[4] = s_c5*(N.x*N.x - N.y*N.y);
}

void ProjectNormalToShOrder3(double coef[9], Vec3 N)
{
	coef[0] = s_c0;
	coef[1] = -s_c1 * N.y;
	coef[2] = s_c1 * N.z;
	coef[3] = -s_c1 * N.x;
	coef[4] = s_c2*N.x*N.y;
	coef[5] = -s_c2*N.y*N.z;
	coef[6] = s_c3*N.z*N.z + s_c4;
	coef[7] = -s_c2*N.x*N.z;
	coef[8] = s_c5*(N.x*N.x - N.y*N.y);
}

void ProjectNormalToShOrder3TestBands(double coef[9], Vec3 N)
{
	ProjectNormalToShBand0(&coef[0],N);
	ProjectNormalToShBand1(&coef[1],N);
	ProjectNormalToShBand2(&coef[4],N);
}

