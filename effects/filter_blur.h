/**********************************************************************************\
	Effect_Blur.h
	
	Blur an image using "Effect_ConvolutionMatrix.h"
\**********************************************************************************/

#ifndef __EFFECT_BLUR_H__
#define __EFFECT_BLUR_H__

namespace imgeffects
{

	/*----------------------------------------*\
		unsigned char* blur_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius);

		bpp := Bits Per Pixel
		Blurs an image with given parameters
		Returns a new buffer, must be deleted
	\*----------------------------------------*/
	unsigned char* blur_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius);
	
	/*----------------------------------------*\
		unsigned char* BlurImage_Gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double blursigma, int blurwidth)

		bpp := Bits Per Pixel
		Blurs an image with given parameters
		Returns a new buffer, must be deleted
	\*----------------------------------------*/
	unsigned char* blur_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius, double sigma);

} // namespace ImageEffects

#endif // #ifndef __EFFECT_BLUR_H__