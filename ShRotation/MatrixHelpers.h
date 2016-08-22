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

#ifndef _MATRIX_HELPERS_H_
#define _MATRIX_HELPERS_H_

#include "Vec3.h"

void MulMatMat3(double dst[3][3], const double lhs[3][3], const double rhs[3][3]);
void MakeRotationMatrixRadians(double dst[3][3], double thetaX, double thetaY, double thetaZ);
double RandomAngleDeg();
void MakeRotationMatrixDegrees(double dst[3][3], double thetaX, double thetaY, double thetaZ);
void MakeRandomRotationMatrix(double dst[3][3]);

Vec3 MulMatVecN(const double lhs[3][3], const Vec3 & N);
void MulMatVec3(double dst[3], const double lhs[3][3], const double rhs[3]);
void MulMatVec3Flat(double dst[3], const double lhs[9], const double rhs[3]);
void MulMatVec5Flat(double dst[5], const double lhs[25], const double rhs[5]);


#endif
