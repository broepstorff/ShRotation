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

#include "MatrixInverse.h"

#include "jama/tnt_array2d.h"
#include "jama/jama_lu.h"

// not much error checking, be careful
void CalcInverseLUDirect(std::vector < double > & dst, const std::vector < double > & A, int size)
{
	TNT::Array2D<double> M(size,size);
	TNT::Array2D<double> identity(size,size);

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
		{
			M[r][c] = A[r*size+c];
			identity[r][c] = (r==c) ? 1.0 : 0.0;
		}

	JAMA::LU<double> lu(M);
	TNT::Array2D<double> invM = lu.solve(identity);
		
	dst.resize(A.size());
	
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			dst[r*size+c] = invM[r][c];
}


