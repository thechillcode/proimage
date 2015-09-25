/**********************************************************************************\
	Effect_Crop.h
	
	Crop an image
\**********************************************************************************/

#ifndef __EFFECTCROP_H__
#define __EFFECTCROP_H__

#include <memory>

namespace imgeffects
{

	/*----------------------------------------*\
		unsigned char* crop(unsigned char* Data, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

		bpp := Bits Per Pixel
		Crop an Image, get a crop rectangle
		Return a new buffer, has be deleted using delete []
	\*----------------------------------------*/
	unsigned char* crop(unsigned char* Data, unsigned int width, unsigned int height, unsigned int bpp, unsigned int x, unsigned int y, unsigned int w, unsigned int h);

	/*----------------------------------------*\
		T* crop_T(T* Data, unsigned int width, unsigned int height, unsigned int bytes_pixel)

		Crop an Image, get a crop rectangle
		Return a new buffer, has be deleted using delete []
		for 8bit channel pass usigned char*, for 16 bit pass unsigned short*
	\*----------------------------------------*/
	template <typename T>
	T* crop_T(T* Data, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
	{
		// Sanity Check
		if ((x + w) > width) return 0;
		if ((y + h) > height) return 0;
		unsigned int bytes_pixel = sizeof(T);
		size_t size = (size_t)w*h;
		unsigned int len = w*bytes_pixel;
		T* pData = Data;
		T* newimg = new T[size];
		T* pnew = newimg;
		unsigned int i = 0, j = 0;

		for (j = y; j<(y + h); j++)
		{
			pData = Data + (j*width) + x;
			memcpy(pnew, pData, len);
			pnew += w;
		}
		return newimg;
	}

} // namespace imgeffects

#endif // #ifndef __EFFECTCROP_H__