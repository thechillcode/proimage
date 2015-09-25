/**********************************************************************************\
	Effect_EdgeDetection.cpp
\**********************************************************************************/

#include "filter_edgedetection.h"
#include "filter_convolute.h"
#include "effect_math.h"

namespace imgeffects
{

/*----------------------------------------*\
	Gx =	
	1 0 -1
	2 0 -2
	1 0 -1
	=>
	1
	2	* (1 0 -1)
	1

	Gy =	
	 1   2   1
	 0   0   0
	-1  -2  -1
	=>
	 1
	 0	* (1 2 1)
	-1
\*----------------------------------------*/

static int G1[] =
{
	1, 2, 1,
};
static int G2[] =
{
	1, 0, -1,
};

unsigned char* edge_detect_sobel(unsigned char* Buff1, unsigned int width, unsigned int height, unsigned int bpp)
{
	ConvolutionMatrix ConvGx;
	ConvGx.add(G2, 3, 1, 1, 0);
	ConvGx.add(G1, 1, 3, 1, 0);

	ConvolutionMatrix ConvGy;
	ConvGy.add(G1, 3, 1, 1, 0);
	ConvGy.add(G2, 1, 3, 1, 0);

	size_t size = width*height;
	unsigned char* G = 0;

	int* Gx = 0;
	int* Gy = 0;

	switch (bpp)
	{
	case 8:
		Gx = convolute_raw_T(Buff1, width, height, &ConvGx);
		Gy = convolute_raw_T(Buff1, width, height, &ConvGy);
		G = (unsigned char*)math_calc_T<int, unsigned char>(Gx, Gy, size, pow2_sqrt_T<int, unsigned char>);
		break;
	case 16:
		Gx = convolute_raw_T((unsigned short*)Buff1, width, height, &ConvGx);
		Gy = convolute_raw_T((unsigned short*)Buff1, width, height, &ConvGy);
		G = (unsigned char*)math_calc_T<int, unsigned short>(Gx, Gy, size, pow2_sqrt_T<int, unsigned short>);
		break;
	}

	if (Gx) delete[] Gx;
	if (Gy) delete[] Gy;

	if (G) return G;
	return 0;
}

/*
unsigned char* DifferenceOfGaussians_Ch8(unsigned char* Buff1, unsigned int width, unsigned int height, unsigned int channels, unsigned int radius)
{
	if (channels == 1)
	{
		unsigned char* pDiff = DifferenceOfGaussians(Buff1, width, height, channels, radius);
		unsigned char* pNorm = NormalizeLinear_Gray8(pDiff, width, height);
		delete [] pDiff;
		return pNorm;
	}
	if (channels == 3)
	{
		unsigned char* pDiff = DifferenceOfGaussians(Buff1, width, height, channels, radius);
		unsigned char* pNorm = NormalizeLinear_RGB24(pDiff, width, height);
		delete [] pDiff;
		return pNorm;
	}
	return 0;
}
*/


} // namespace ImageEffects
