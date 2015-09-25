/**********************************************************************************\
	Effect_FormatConversion.h
	
	Change Buffer between different Formats
\**********************************************************************************/

#ifndef __EFFECT_FORMATCONVERSION_H__
#define __EFFECT_FORMATCONVERSION_H__

namespace imgeffects
{

	/*--------------------------------------------------------------------------------*\
		unsigned char* convert_rgb_to_gray(unsigned char* pRed, unsigned char* pGreen, unsigned char* pBlue, unsigned int width, unsigned int height, unsigned int bpp)

		convert any rgb buffer 8/16 bit to and 8/16 bit gray scale buffer
		user must delete returned buffer
	\*--------------------------------------------------------------------------------*/
	unsigned char* convert_rgb_to_gray(unsigned char* pRed, unsigned char* pGreen, unsigned char* pBlue, unsigned int width, unsigned int height, unsigned int bpp);


	unsigned char* convert_rgb_to_mono(unsigned char* pRed, unsigned char* pGreen, unsigned char* pBlue, unsigned int width, unsigned int height, unsigned int bpp, unsigned int threshold);

	/*--------------------------------------------------------------------------------*\
		void convert_gray8_to_mono8(unsigned char* pGray, unsigned char* pMono, unsigned int width, unsigned int height, unsigned char threshold);

		threshold [0,255]
		BufferGray and BufferMono could be the same buffer.
	\*--------------------------------------------------------------------------------*/
	unsigned char* convert_gray_to_mono(unsigned char* pGray, unsigned int width, unsigned int height, unsigned int bpp, unsigned int threshold);

} // namespace ImageEffects

#endif // #ifndef __EFFECT_FORMATCONVERSION_H__