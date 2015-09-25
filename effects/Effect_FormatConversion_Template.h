/**********************************************************************************\
	Effect_FormatConversion.h
	
	Change Buffer between different Formats
\**********************************************************************************/

#ifndef __EFFECT_FORMATCONVERSION_TEMPLATE_H__
#define __EFFECT_FORMATCONVERSION_TEMPLATE_H__

#include "Effect_FormatConversion_Definitions.h"

namespace imgeffects
{

/*----------------------------------------*\
	unsigned char* Convert_RGB24_Gray8(unsigned char* pRed, unsigned char* pGreen, unsigned char* pBlue, unsigned char* pGray, size_t size);

	Convert 3 RGB Buffers to one Gray Buffer
	size is for all buffers the same
\*----------------------------------------*/
template <class T>
void convert_rgb_to_grayscale_T(T* pRed, T* pGreen, T* pBlue, T* pGray, unsigned int width, unsigned int height)
{
	size_t size = size_t(width)*height;
	for (size_t i=0; i<size; i++)
	{
		*pGray++ = (T)RGBTOGRAY(*pRed++, *pGreen++, *pBlue++);
	}
}

template <class T>
T* convert_rgb_to_grayscale_T(T* pRed, T* pGreen, T* pBlue, unsigned int width, unsigned int height)
{
	size_t size = size_t(width)*height;
	T* pGray = new T[size];
	convert_rgb_to_grayscale_T(pRed, pGreen, pBlue, pGray, width, height);
	return pGray;
}

/*----------------------------------------*\
	void convert_rgb_to_monochrome (T* pRed, T* pGreen, T* pBlue, T* pMono, unsigned int width, unsigned int height, T threshold)

	Convert 3 RGB Buffers to one Gray Buffer
	size is for all buffers the same
\*----------------------------------------*/
template <class T>
void convert_rgb_to_monochrome_T(T* pRed, T* pGreen, T* pBlue, T* pMono, unsigned int width, unsigned int height, T threshold)
{
	size_t size = size_t(width)*height;
	T max = ~0;
	for (size_t i=0; i<size; i++)
	{
		*pMono++ = (T)MONO(RGBTOGRAY(*pRed++, *pGreen++, *pBlue++), threshold, max);
	}
}

template <class T>
T* convert_rgb_to_monochrome_T(T* pRed, T* pGreen, T* pBlue, unsigned int width, unsigned int height, T threshold)
{
	size_t size = size_t(width)*height;
	T* pMono = new T[size];
	convert_rgb_to_monochrome_T(pRed, pGreen, pBlue, pMono, width, height, threshold);
	return pMono;
}

/*----------------------------------------*\
	void Convert_Gray_Mono(unsigned char* pGray, unsigned char* pMono, unsigned int width, unsigned int height, unsigned char threshold);

	threshold [0,255]
	BufferGray and BufferMono could be the same buffer.
\*----------------------------------------*/
template <class T>
void convert_grayscale_to_monochrome_T(T* pGray, T* pMono, unsigned int width, unsigned int height, T threshold)
{
	size_t size = size_t(width)*height;
	T max = ~0;
	for (size_t i=0; i<size; i++)
	{
		*pMono++ = MONO(*pGray++, threshold, max);
	}
}

template <class T>
T* convert_grayscale_to_monochrome_T(T* pGray, unsigned int width, unsigned int height, T threshold)
{
	size_t size = size_t(width)*height;
	T* pMono = new T[size];
	convert_grayscale_to_monochrome_T(pGray, pMono, width, height, threshold);
	return pMono;
}

} // namespace imgeffects

#endif // #ifndef __EFFECT_FORMATCONVERSION_TEMPLATE_H__