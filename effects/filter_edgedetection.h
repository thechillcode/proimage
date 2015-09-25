/**********************************************************************************\
	Effect_EdgeDetection.h
\**********************************************************************************/

#ifndef __EFFECT_EDGEDETECTION_H__
#define __EFFECT_EDGEDETECTION_H__

namespace imgeffects
{

/*----------------------------------------*\
	unsigned char* edge_detect_Sobel(unsigned char* Buff1, unsigned int width, unsigned int height, unsigned int bpp)

	bpp := number of bits per pixel
	for 8 bit color channels
	Uses Convolution Matrix and Math
	Returns a new Buffer, must be deleted
\*----------------------------------------*/
unsigned char* edge_detect_sobel(unsigned char* Buff1, unsigned int width, unsigned int height, unsigned int bpp);

/*----------------------------------------*\
	unsigned char* DifferenceOfGaussians_8bit(unsigned char* Buff1, unsigned int width, unsigned int height, unsigned int channels, unsigned int radius)

	for 8 bit color channels
	Substracts a blured image from the original image, returns absolute image normalized
	Returns a new Buffer, must be deleted
\*----------------------------------------*/
//unsigned char* DifferenceOfGaussians_Ch8(unsigned char* Buff1, unsigned int width, unsigned int height, unsigned int radius);


} // namespace ImageEffects

#endif // #ifndef __EFFECT_EDGEDETECTION_H__