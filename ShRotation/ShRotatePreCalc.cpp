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

#include "ShRotatePreCalc.h"

#include "MatrixHelpers.h"
#include "ShProject.h"

#include <vector>

const static double s_inv_sqrt_2 = 0.70710678118;

void PreCalcRotateBand0(double dst[1], const double src[1], const double mat[3][3])
{
	dst[0] = src[0];
}


void ProjectNormalToShBand1NoScale(double coef[3], Vec3 N)
{
	coef[0] = -N.y;
	coef[1] = N.z;
	coef[2] = -N.x;
}

void PreCalcRotateBand1(double dst[3], const double src[3], const double mat[3][3])
{
	// derived from  SlowRotateBand1
	dst[0] = ( mat[1][1])*src[0] + (-mat[1][2])*src[1] + ( mat[1][0])*src[2];
	dst[1] = (-mat[2][1])*src[0] + ( mat[2][2])*src[1] + (-mat[2][0])*src[2];
	dst[2] = ( mat[0][1])*src[0] + (-mat[0][2])*src[1] + ( mat[0][0])*src[2];
}

void PreCalcRotateBand2(double dst[5], const double src[5], const double mat[3][3])
{
	Vec3 r0 = Vec3(1,0,0);
	Vec3 r1 = Vec3(0,0,1);
	Vec3 r2 = Vec3(s_inv_sqrt_2,s_inv_sqrt_2,0);
	Vec3 r3 = Vec3(s_inv_sqrt_2,0,s_inv_sqrt_2);
	Vec3 r4 = Vec3(0,s_inv_sqrt_2,s_inv_sqrt_2);

	const static double s_rc0 = 0.91529123286551084;
	const static double s_rc1 = 0.91529123286551084*2.0;
	const static double s_rc2 = 1.5853309190550713;

	double matInv[25] = 
	{
		0,     -s_rc0,      0, s_rc0, s_rc1,	
		s_rc0,      0, s_rc2,  s_rc0, s_rc0,	
		s_rc1,      0,      0,     0,      0,	
		0,          0,      0,-s_rc1,      0,	
		0,     -s_rc1,      0,     0,      0,
	};

	Vec3 rot0;
	Vec3 rot1;
	Vec3 rot2;
	Vec3 rot3;
	Vec3 rot4;
	rot0 = MulMatVecN(mat,r0);
	rot1 = MulMatVecN(mat,r1);
	rot2 = MulMatVecN(mat,r2);
	rot3 = MulMatVecN(mat,r3);
	rot4 = MulMatVecN(mat,r4);

	double proj_trans[5][5];
	ProjectNormalToShBand2(proj_trans[0],rot0);
	ProjectNormalToShBand2(proj_trans[1],rot1);
	ProjectNormalToShBand2(proj_trans[2],rot2);
	ProjectNormalToShBand2(proj_trans[3],rot3);
	ProjectNormalToShBand2(proj_trans[4],rot4);

	// once again, set each column to each vector
	std::vector < double > projData(25);
	for (int r = 0; r < 5; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			projData[r*5+c] = proj_trans[c][r];
		}
	}

	double tempVec[5];
	MulMatVec5Flat(tempVec,&matInv[0],src);
	MulMatVec5Flat(dst,&projData[0],tempVec);
}

void PreCalcRotateOrder3(double dst[9], const double src[9], const double mat[3][3])
{
	PreCalcRotateBand0(&dst[0],&src[0],mat);
	PreCalcRotateBand1(&dst[1],&src[1],mat);
	PreCalcRotateBand2(&dst[4],&src[4],mat);
}

