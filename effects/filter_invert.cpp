/**========================================================================================================================**\
	Effect_InvertImage.cpp
\**========================================================================================================================**/

#include "filter_invert.h"

namespace proimage
{

	template <class T>
	T* invert_T(T* data, unsigned int width, unsigned int height)
	{
		size_t size = size_t(width)*height;
		// new image
		T* new_data = new T[size];
		T* p_new_data = new_data;
		size_t i = 0;
		for (i = 0; i<size; i++)
		{
			*p_new_data++ = ~(*data++);
		}
		return new_data;
	}

	// use same image
	template <class T>
	void invert_update_T(T* data, unsigned int width, unsigned int height)
	{
		size_t size = size_t(width)*height;
		size_t i = 0;
		for (i = 0; i<size; i++)
		{
			*data = ~(*data);
			data++;
		}
	}


unsigned char* invert (unsigned char* data, unsigned int width, unsigned int height, unsigned int bpp)
{
	switch (bpp)
	{
	case 8:
		return invert_T((unsigned char*)data, width, height);
	case 16:
		return (unsigned char*)invert_T((unsigned short*)data, width, height);
	}
	return 0;
}

void invert_update(unsigned char* data, unsigned int width, unsigned int height, unsigned int bpp)
{
	switch (bpp)
	{
	case 8:
		invert_update_T((unsigned char*)data, width, height);
		break;
	case 16:
		invert_update_T((unsigned short*)data, width, height);
		break;
	}
}

} // namepace imgeffects