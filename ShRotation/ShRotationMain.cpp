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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <vector>
#include <assert.h>

#include "MatrixInverse.h"
#include "MatrixHelpers.h"
#include "Vec3.h"

#include "ShProject.h"
#include "ShRotateSlow.h"
#include "ShRotatePreCalc.h"
#include "ShRotateFast.h"

int main(int argc, const char * argv[])
{
	srand(200);

	double errSqrA = 0;
	double errSqrB = 0;
	double errSqrC = 0;

	int numIter = 1000;
	for (int iter = 0; iter < numIter; iter++)
	{
		double rotationMat[3][3];
		MakeRandomRotationMatrix(rotationMat);

		Vec3 srcVec = Vec3::RandomNormal();

		double shRef[9], shA[9], shB[9], shC[9];

		// rotate then project (reference)
		{
			Vec3 rotVec = MulMatVecN(rotationMat,srcVec);
			ProjectNormalToShOrder3(shRef,rotVec);
		}

		// project then rotate
		{
			double projSh[9];
			ProjectNormalToShOrder3(projSh,srcVec);
			SlowRotateOrder3(shA,projSh,rotationMat);
			PreCalcRotateOrder3(shB,projSh,rotationMat);
			OptRotateOrder3(shC,projSh,rotationMat);
		}

		for (int i = 0; i < 9; i++)
		{
			double diffA = shRef[i] - shA[i];
			errSqrA += diffA*diffA;
			double diffB = shRef[i] - shB[i];
			errSqrB += diffB*diffB;
			double diffC = shRef[i] - shC[i];
			errSqrC += diffC*diffC;
		}
	}

	double rmsErrA = sqrt(errSqrA)/double(numIter);
	printf("Rms Err A: %g\n", rmsErrA);
			
	double rmsErrB = sqrt(errSqrB)/double(numIter);
	printf("Rms Err B: %g\n", rmsErrB);
			
	double rmsErrC = sqrt(errSqrC)/double(numIter);
	printf("Rms Err C: %g\n", rmsErrC);
			


	getchar();

	return EXIT_SUCCESS;
}