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

#include "ShRotateFast.h"

// 0 multiplies
void OptRotateBand0(double dst[1], const double src[1], const double mat[3][3])
{
	dst[0] = src[0];
}

// 9 multiplies
void OptRotateBand1(double dst[3], const double src[3], const double mat[3][3])
{
	// derived from  SlowRotateBand1
	dst[0] = ( mat[1][1])*src[0] + (-mat[1][2])*src[1] + ( mat[1][0])*src[2];
	dst[1] = (-mat[2][1])*src[0] + ( mat[2][2])*src[1] + (-mat[2][0])*src[2];
	dst[2] = ( mat[0][1])*src[0] + (-mat[0][2])*src[1] + ( mat[0][0])*src[2];
}

const static double s_c3 = 0.94617469575; // (3*sqrt(5))/(4*sqrt(pi))
const static double s_c4 = -0.31539156525;// (-sqrt(5))/(4*sqrt(pi))
const static double s_c5 = 0.54627421529; // (sqrt(15))/(4*sqrt(pi))

const static double s_c_scale = 1.0/0.91529123286551084;
const static double s_c_scale_inv = 0.91529123286551084;

const static double s_rc2 = 1.5853309190550713*s_c_scale;
const static double s_c4_div_c3 = s_c4/s_c3;
const static double s_c4_div_c3_x2 = (s_c4/s_c3)*2.0;

const static double s_scale_dst2 = s_c3 * s_c_scale_inv;
const static double s_scale_dst4 = s_c5 * s_c_scale_inv;

// 48 multiplies
void OptRotateBand2(double dst[5], const double x[5],
								  double m00, double m01, double m02,
								  double m10, double m11, double m12,
								  double m20, double m21, double m22)
{
	// Sparse matrix multiply
	double sh0 =  x[3] + x[4] + x[4] - x[1];
	double sh1 =  x[0] + s_rc2*x[2] +  x[3] + x[4];
	double sh2 =  x[0];
	double sh3 = -x[3];
	double sh4 = -x[1];

	// Rotations.  R0 and R1 just use the raw matrix columns
	double r2x = m00 + m01;
	double r2y = m10 + m11;
	double r2z = m20 + m21;

	double r3x = m00 + m02;
	double r3y = m10 + m12;
	double r3z = m20 + m22;

	double r4x = m01 + m02;
	double r4y = m11 + m12;
	double r4z = m21 + m22;

	// dense matrix multiplication one column at a time
	
	// column 0
	double sh0_x = sh0 * m00;
	double sh0_y = sh0 * m10;
	double d0 = sh0_x * m10;
	double d1 = sh0_y * m20;
	double d2 = sh0 * (m20 * m20 + s_c4_div_c3);
	double d3 = sh0_x * m20;
	double d4 = sh0_x * m00 - sh0_y * m10;
	
	// column 1
	double sh1_x = sh1 * m02;
	double sh1_y = sh1 * m12;
	d0 += sh1_x * m12;
	d1 += sh1_y * m22;
	d2 += sh1 * (m22 * m22 + s_c4_div_c3);
	d3 += sh1_x * m22;
	d4 += sh1_x * m02 - sh1_y * m12;
	
	// column 2
	double sh2_x = sh2 * r2x;
	double sh2_y = sh2 * r2y;
	d0 += sh2_x * r2y;
	d1 += sh2_y * r2z;
	d2 += sh2 * (r2z * r2z + s_c4_div_c3_x2);
	d3 += sh2_x * r2z;
	d4 += sh2_x * r2x - sh2_y * r2y;

	// column 3
	double sh3_x = sh3 * r3x;
	double sh3_y = sh3 * r3y;
	d0 += sh3_x * r3y;
	d1 += sh3_y * r3z;
	d2 += sh3 * (r3z * r3z + s_c4_div_c3_x2);
	d3 += sh3_x * r3z;
	d4 += sh3_x * r3x - sh3_y * r3y;

	// column 4
	double sh4_x = sh4 * r4x;
	double sh4_y = sh4 * r4y;
	d0 += sh4_x * r4y;
	d1 += sh4_y * r4z;
	d2 += sh4 * (r4z * r4z + s_c4_div_c3_x2);
	d3 += sh4_x * r4z;
	d4 += sh4_x * r4x - sh4_y * r4y;

	// extra multipliers
	dst[0] = d0;
	dst[1] = -d1;
	dst[2] = d2 * s_scale_dst2;
	dst[3] = -d3;
	dst[4] = d4 * s_scale_dst4;
}

void OptRotateOrder3(double dst[9], const double src[9], const double mat[3][3])
{
	OptRotateBand0(&dst[0],&src[0],mat);
	OptRotateBand1(&dst[1],&src[1],mat);
	OptRotateBand2(&dst[4], &src[4],
		mat[0][0],mat[0][1],mat[0][2],
		mat[1][0],mat[1][1],mat[1][2],
		mat[2][0],mat[2][1],mat[2][2]);
}


