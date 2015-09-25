/**********************************************************************************\
	Effect_Normalization.cpp
\**********************************************************************************/

#include "filter_normalize.h"
#include <memory>

namespace imgeffects
{

	template <class T>
	void normalize_linear_get_min_max_T(T* Data, size_t size, T* min, T* max)
	{
		// find min and max
		size_t i = 0;
		T imgmin = T(~0);
		T imgmax = 0;
		T* pData = Data;
		T curval = 0;
		for (i = 0; i<size; i++)
		{
			curval = *pData++;
			if (curval < imgmin) imgmin = curval;
			if (curval > imgmax) imgmax = curval;
		}
		*max = imgmax;
		*min = imgmin;
	}

	template <class T>
	T* normalize_linear_T(T* Data, unsigned int width, unsigned int height)
	{
		// find min and max
		size_t size = width*height;
		size_t i = 0;
		T imgmin = 0;
		T imgmax = 0;
		T _max = ~0;

		normalize_linear_get_min_max_T(Data, size, &imgmin, &imgmax);

		T* newimg = new T[size];

		if ((imgmin == 0) && (imgmax == _max))
		{
			memcpy(newimg, Data, size*sizeof(T));
			return newimg;
		}

		T* pData = Data;
		T curval = 0;
		
		T _dist = imgmax - imgmin;
		double ratio = double(_max) / (_dist);

		T* pnewimg = newimg;
		int value = 0;
		for (i = 0; i<size; i++)
		{
			curval = *pData++ - imgmin;
			*pnewimg++ = T((ratio * curval) + 0.5);
		}
		return newimg;
	}

	template <class T>
	void normalize_linear_update_T(T* Data, unsigned int width, unsigned int height)
	{
		// find min and max
		size_t size = width*height;
		size_t i = 0;
		T imgmin = 0;
		T imgmax = 0;
		T _max = ~0;

		normalize_linear_get_min_max_T(Data, size, &imgmin, &imgmax);

		if ((imgmin == 0) && (imgmax == _max)) return;

		T* pData = Data;
		T curval = 0;

		T _dist = imgmax - imgmin;
		double ratio = double(_max) / (_dist);

		int value = 0;
		for (i = 0; i<size; i++)
		{
			curval = *pData - imgmin;
			*pData++ = T((ratio * curval) + 0.5);
		}
	}

	unsigned char* normalize_linear(unsigned char* Data, unsigned int width, unsigned int height, unsigned int bpp)
	{
		switch (bpp)
		{
		case 8:
			return normalize_linear_T(Data, width, height);
		case 16:
			return (unsigned char*)normalize_linear_T((unsigned short*)Data, width, height);
		}
		return 0;
	}

	void normalize_linear_update(unsigned char* Data, unsigned int width, unsigned int height, unsigned int bpp)
	{
		switch (bpp)
		{
		case 8:
			normalize_linear_update_T(Data, width, height);
			break;
		case 16:
			normalize_linear_update_T((unsigned short*)Data, width, height);
			break;
		}
	}

} // namespace ImageEffects
