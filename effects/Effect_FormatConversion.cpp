/**********************************************************************************\
	Effect_FormatConversion.cpp
	
	Change Buffer between different Formats
\**********************************************************************************/

#include "Effect_FormatConversion.h"
#include "Effect_FormatConversion_Template.h"
#include "Effect_FormatConversion_Definitions.h"

namespace proimage
{

	unsigned char* convert_rgb_to_gray(unsigned char* pRed, unsigned char* pGreen, unsigned char* pBlue, unsigned int width, unsigned int height, unsigned int bpp)
	{
		switch (bpp)
		{
		case 8:
			return convert_rgb_to_grayscale_T<unsigned char>(pRed, pGreen, pBlue, width, height);
		case 16:
			return (unsigned char*)convert_rgb_to_grayscale_T<unsigned short>((unsigned short*)pRed, (unsigned short*)pGreen, (unsigned short*)pBlue, width, height);
		}
		return 0;
	}

	unsigned char* convert_rgb_to_mono(unsigned char* pRed, unsigned char* pGreen, unsigned char* pBlue, unsigned int width, unsigned int height, unsigned int bpp, unsigned int threshold)
	{
		switch (bpp)
		{
		case 8:
			return convert_rgb_to_monochrome_T<unsigned char>(pRed, pGreen, pBlue, width, height, (unsigned char)threshold);
		case 16:
			return (unsigned char*)convert_rgb_to_monochrome_T<unsigned short>((unsigned short*)pRed, (unsigned short*)pGreen, (unsigned short*)pBlue, width, height, (unsigned short)threshold);
		}
		return 0;
	}

	unsigned char* convert_gray_to_mono(unsigned char* pgray, unsigned int width, unsigned int height, unsigned int bpp, unsigned int threshold)
	{
		switch (bpp)
		{
		case 8:
			return convert_grayscale_to_monochrome_T<unsigned char>(pgray, width, height, (unsigned char)threshold);
		case 16:
			return (unsigned char*)convert_grayscale_to_monochrome_T<unsigned short>((unsigned short*)pgray, width, height, (unsigned short)threshold);
		}
		return 0;
	}

} // namespace ImageEffects
