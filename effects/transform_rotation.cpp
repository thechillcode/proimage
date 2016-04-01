/**********************************************************************************\
	Effect_Rotation.cpp
	
	Rotate an image
	For fine rotation GDI+ is used
\**********************************************************************************/

#include "transform_matrix.h"
#include "transform_rotation.h"
#include "EFFECTS_DEFINES.h"

namespace proimage
{

	/*----------------------------------------*\
	unsigned char* rotate_270(unsigned char* pBuff, unsigned int width, unsigned int height);

	Rotate an image by 90 degress counter clock wize, or 270 clock wize
	width and height are swaped.
	Return a new buffer, has be deleted using delete []
	\*----------------------------------------*/
	template <typename T>
	T* rotate_channel_270(T* pBuff, unsigned int width, unsigned int height)
	{
		// Width and height of new image
		size_t size = size_t(width)*height;
		unsigned int _width = height;
		unsigned int _height = width;

		T* pnewimg = new T[size];
		T* pix = 0;
		_height -= 1;

		unsigned int i = 0, j = 0;
		for (j = 0; j<height; j++)
		{
			for (i = 0; i<width; i++)
			{
				// pixel in new image
				pix = pnewimg + ((_height - i)*_width) + (j);
				*pix = *pBuff++;
			}
		}
		return pnewimg;
	}

	/*----------------------------------------*\
	unsigned char* rotate_180(unsigned char* pBuff, unsigned int width, unsigned int height);

	Rotate an image by 180 degress counter clock wize
	Return a new buffer, has be deleted using delete []
	\*----------------------------------------*/
	template <typename T>
	T* rotate_channel_180(T* pBuff, unsigned int width, unsigned int height)
	{
		size_t size = (size_t)width*height;
		T* pnewimg = new T[size];
		T* p_img = pnewimg + (size)-1;

		size_t i = 0;
		for (i = 0; i<size; i++)
		{
			*p_img-- = *pBuff++;
		}
		return pnewimg;
	}

	/*----------------------------------------*\
	unsigned char* rotate_90(unsigned char* pBuff, unsigned int width, unsigned int height);

	Rotate an image by 270 degress counter clock wize, or 90 clock wize
	width and height are swaped.
	Return a new buffer, has be deleted using delete []
	\*----------------------------------------*/
	template <typename T>
	T* rotate_channel_90(T* pBuff, unsigned int width, unsigned int height)
	{
		size_t size = size_t(width)*height;
		unsigned int _width = height;
		unsigned int _height = width;
		int _stride = _width;

		T* pnewimg = new T[size];
		T* pix = 0;

		unsigned int i = 0, j = 0;
		for (j = 0; j<height; j++)
		{
			for (i = 0; i<width; i++)
			{
				// pixel in new image
				pix = pnewimg + (i*_stride) + (_stride - 1 - (j));
				*pix = *pBuff++;
			}
		}
		return pnewimg;
	}

unsigned char* rotate_90(unsigned char* img, unsigned int width, unsigned int height, unsigned int bpp)
{
	switch (bpp)
	{
	case 8:
		return rotate_channel_90(img, width, height);
	case 16:
		return (unsigned char*)rotate_channel_90((unsigned short*)img, width, height);
	}
	return 0;
}

unsigned char* rotate_180(unsigned char* img, unsigned int width, unsigned int height, unsigned int bpp)
{
	switch (bpp)
	{
	case 8:
		return rotate_channel_180(img, width, height);
	case 16:
		return (unsigned char*)rotate_channel_180((unsigned short*)img, width, height);
	}
	return 0;
}

unsigned char* rotate_270(unsigned char* img, unsigned int width, unsigned int height, unsigned int bpp)
{
	switch (bpp)
	{
	case 8:
		return rotate_channel_270(img, width, height);
	case 16:
		return (unsigned char*)rotate_channel_270((unsigned short*)img, width, height);
	}
	return 0;
}

unsigned char* rotate_rad(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, float angle, double rot_x, double rot_y, unsigned int* new_width, unsigned int* new_height)
{
	TransformMatrix tm;
	tm.add_rotation_rad(double(angle), rot_x, rot_y);
	return transform(pBuff, width, height, bpp, &tm, new_width, new_height);
}

unsigned char* rotate(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, float angle, double rot_x, double rot_y, unsigned int* new_width, unsigned int* new_height)
{
	return rotate_rad(pBuff, width, height, bpp, float(DEGTORAD(angle)), rot_x, rot_y, new_width, new_height);
}

} // namespace ImageEffects
