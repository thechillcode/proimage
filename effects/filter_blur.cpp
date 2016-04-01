/**********************************************************************************\
	Effect_Blur.cpp
\**********************************************************************************/

#include "EFFECTS_DEFINES.h"
#include "filter_blur.h"
#include "filter_convolute.h"
#include "calc_gauss_kernel.h"

namespace proimage
{

unsigned char* blur_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius, double sigma)
{
	int blurwidth = (radius * 2) + 1;
	int sum = 0;
	int* Gauss1D = gauss_get_kernel(sigma, blurwidth, &sum);
	ConvolutionMatrix BlurMatrix;
	BlurMatrix.add(Gauss1D, blurwidth, 1, sum, 0);
	BlurMatrix.add(Gauss1D, 1, blurwidth, sum, 0);
	delete[] Gauss1D;
	unsigned char* pBuffOut = 0;
	pBuffOut = convolute(pBuff, width, height, bpp, &BlurMatrix);
	if (pBuffOut) return pBuffOut;
	return 0;
}

// Radius in pixels
unsigned char* blur_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius)
{
	double sigma = gauss_get_sigma_from_radius(radius);
	return blur_gauss(pBuff, width, height, bpp, radius, sigma);
}

} // namespace ImageEffects
