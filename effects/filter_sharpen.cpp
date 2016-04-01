/**********************************************************************************\
	Effect_Blur.cpp
\**********************************************************************************/

#include "EFFECTS_DEFINES.h"
#include "filter_sharpen.h"
#include "filter_convolute.h"
#include "calc_gauss_kernel.h"

namespace proimage
{

unsigned char* sharpen_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius, double sigma)
{
	int sharpwidth = (radius * 2) + 1;
	int sum = 0;
	int* Gauss1D = gauss_get_kernel(sigma, sharpwidth, &sum);
	ConvolutionMatrix BlurMatrix;
	BlurMatrix.add(Gauss1D, sharpwidth, 1, sum, 0);
	BlurMatrix.add(Gauss1D, 1, sharpwidth, sum, 0);
	unsigned char* pBuffOut = 0;
	pBuffOut = convolute(pBuff, width, height, bpp, &BlurMatrix);
	delete [] Gauss1D;
	if (!pBuffOut) return 0;
	// substract image from 2x original (2*O - Blur)
	size_t size = size_t(width)*height;
	switch (bpp)
	{
	case 8:
		{
			unsigned char* p_in = pBuff;
			unsigned char* p_out = pBuffOut;
			double in = 0;
			double blur = 0;
			double sharp = 0;
			for (size_t i=0; i<size; i++)
			{
				in = (double)*p_in;
				blur = (double)*p_out;
				sharp = (in * 2) - (blur);
				*p_out = unsigned char(CONSTRAIN(sharp,0,255));
				p_in++;
				p_out++;
			}
		}
		break;

	case 16:
		{
			unsigned short* p_in = (unsigned short*)pBuff;
			unsigned short* p_out = (unsigned short*)pBuffOut;
			for (size_t i=0; i<size; i++)
			{
				*p_out = unsigned short((int(*p_in)*2)-*p_out);
				p_in++;
				p_out++;
			}
		}
		break;
	}

	return pBuffOut;
}

// Radius in pixels
unsigned char* sharpen_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius)
{
	double sigma = gauss_get_sigma_from_radius(radius);
	return sharpen_gauss(pBuff, width, height, bpp, radius, sigma);
}

} // namespace ImageEffects
