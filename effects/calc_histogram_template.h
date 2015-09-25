/**========================================================================================================================**\
	calc_histogram_template.h
\**========================================================================================================================**/

#ifndef __CALC_HISTORGRAM_TEMPLATE__
#define __CALC_HISTORGRAM_TEMPLATE__

#include <memory>

namespace imgeffects
{
	template <class T>
	size_t* calc_histogram_T(T* buffer, unsigned int width, unsigned int height, size_t* entries)
	{
		size_t num_values = T(~0);
		size_t i = 0, j = 0;
		size_t* histo = new size_t[num_values];
		memset((void*)histo, 0, num_values*sizeof(size_t));
		*entries = num_values;
		T* pline = 0;

		for (j = 0; j < height; j++)
		{
			pline = buffer + (j*width);
			for (i = 0; i < width; i++)
			{
				(histo[*pline++])++;
			}
		}
		return histo;
	}

	template <class T>
	size_t* calc_histogram_width_T(T* buffer, unsigned int width, unsigned int height)
	{
		size_t* histo = new size_t[width];
		size_t max = T(~0)*height;
		size_t i = 0, j = 0;
		size_t sum = 0;

		// Only run through needed lines
		for (i = 0; i < width; i++)
		{
			sum = 0;
			for (j = 0; j < height; j++)
			{
				sum += *(buffer + (j*width) + i);
			}
			histo[i] = sum;
		}
		return histo;
	}

	template <class T>
	size_t* calc_histogram_height_T(T* buffer, unsigned int width, unsigned int height)
	{
		size_t* histo = new size_t[height];
		size_t max = T(~0)*width;
		size_t i = 0, j = 0;
		size_t sum = 0;
		T* pline = 0;

		for (j = 0; j<height; j++)
		{
			pline = buffer + (j*width);
			sum = 0;
			for (i = 0; i<width; i++)
			{
				sum += *pline++;
			}
			histo[j] = sum;
		}
		return histo;
	}

} // namespace imgeffects

#endif // #ifndef __CALC_HISTORGRAM_TEMPLATE__