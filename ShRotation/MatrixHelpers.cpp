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

#include "MatrixHelpers.h"

#include <math.h>
#include <memory.h>
#include <stdlib.h>

void MulMatMat3(double dst[3][3], const double lhs[3][3], const double rhs[3][3])
{
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			double sum = 0;
			for (int i = 0; i < 3; i++)
			{
				sum += lhs[r][i] * rhs[i][c];
			}
			dst[r][c] = sum;
		}
	}
}

void MakeRotationMatrixRadians(double dst[3][3], double thetaX, double thetaY, double thetaZ)
{
	double rotX[3][3];
	double rotY[3][3];
	double rotZ[3][3];

	double cx = cos(thetaX);
	double cy = cos(thetaY);
	double cz = cos(thetaZ);

	double sx = sin(thetaX);
	double sy = sin(thetaY);
	double sz = sin(thetaZ);

	memset(rotX,0,sizeof(rotX));
	memset(rotY,0,sizeof(rotY));
	memset(rotZ,0,sizeof(rotZ));

	rotX[0][0] = 1.0f;
	rotX[1][1] = cx;
	rotX[1][2] = -sx;
	rotX[2][1] = sx;
	rotX[2][2] = cx;

	rotY[0][0] = cy;
	rotY[0][2] = sy;
	rotY[1][1] = 1.0f;
	rotY[2][0] = -sy;
	rotY[2][2] = cy;

	rotZ[0][0] = cz;
	rotZ[0][1] = -sz;
	rotZ[1][0] = sz;
	rotZ[1][1] = cz;
	rotZ[2][2] = 1.0f;

	double rotZY[3][3];
	MulMatMat3(rotZY,rotZ,rotY);
	MulMatMat3(dst,rotZY,rotX);

}

// random angle between [-180, 180)
double RandomAngleDeg()
{
	int val = rand()%3600;
	double ret = (double(val)/100.0)-180.0;
	return ret;
}

static const double s_degToRad = 3.14159265359/180.0;

void MakeRotationMatrixDegrees(double dst[3][3], double thetaX, double thetaY, double thetaZ)
{
	double thetaRadX = s_degToRad * thetaX;
	double thetaRadY = s_degToRad * thetaY;
	double thetaRadZ = s_degToRad * thetaZ;

	MakeRotationMatrixRadians(dst,thetaRadX,thetaRadY,thetaRadZ);
}


void MakeRandomRotationMatrix(double dst[3][3])
{
	double thetaX = RandomAngleDeg();
	double thetaY = RandomAngleDeg();
	double thetaZ = RandomAngleDeg();

	MakeRotationMatrixDegrees(dst,thetaX,thetaY,thetaZ);
}

Vec3 MulMatVecN(const double lhs[3][3], const Vec3 & N)
{
	Vec3 ret;
	ret.x = lhs[0][0] * N.x + lhs[0][1] * N.y + lhs[0][2] * N.z;
	ret.y = lhs[1][0] * N.x + lhs[1][1] * N.y + lhs[1][2] * N.z;
	ret.z = lhs[2][0] * N.x + lhs[2][1] * N.y + lhs[2][2] * N.z;
	return ret;
}

void MulMatVec3(double dst[3], const double lhs[3][3], const double rhs[3])
{
	for (int r = 0; r < 3; r++)
	{
		double sum = 0.0f;
		for (int c = 0; c < 3; c++)
			sum += lhs[r][c]*rhs[c];
		dst[r] = sum;
	}
}

void MulMatVec3Flat(double dst[3], const double lhs[9], const double rhs[3])
{
	for (int r = 0; r < 3; r++)
	{
		double sum = 0.0f;
		for (int c = 0; c < 3; c++)
			sum += lhs[r*3+c]*rhs[c];
		dst[r] = sum;
	}
}

void MulMatVec5Flat(double dst[5], const double lhs[25], const double rhs[5])
{
	for (int r = 0; r < 5; r++)
	{
		double sum = 0.0f;
		for (int c = 0; c < 5; c++)
			sum += lhs[r*5+c]*rhs[c];
		dst[r] = sum;
	}
}

