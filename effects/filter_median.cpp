/**========================================================================================================================**\
	Effect_MediaFilter.cpp
\**========================================================================================================================**/

#include "filter_median.h"

#include <algorithm>

namespace proimage
{

	template <class T>
	T* median_filter_T(T* data, unsigned int width, unsigned int height, unsigned int pixels);

unsigned char* median_filter (unsigned char* data, unsigned int width, unsigned int height, unsigned int bpp, unsigned int pixels)
{
	switch (bpp)
	{
	case 8:
		return median_filter_T((unsigned char*)data, width, height, pixels);
	case 16:
		return (unsigned char*)median_filter_T((unsigned short*)data, width, height, pixels);
	}
	return 0;
}

/*--------------------------------------------------------------------------------*\
	Simple Median Filter
\*--------------------------------------------------------------------------------*/
template <class T>
int compare_ascending(const void *a, const void *b)
{
	return int(*(T*)a - *(T*)b);
}

template <class T>
T* median_filter_T(T* data, unsigned int width, unsigned int height, unsigned int pixels)
{
	size_t size = size_t(width)*height;
	unsigned int square_width = pixels * 2 + 1;
	size_t square_size = square_width * square_width;
	unsigned int middle = int(square_size)/2;
	unsigned int row = 0, col = 0;
	unsigned int row2 = 0, col2 = 0;

	T* data_row = 0;
	T* data_out_row = 0;

	unsigned int _width = width - (pixels * 2);
	unsigned int _height = height - pixels;
	T* mtx = new T[square_size];
	T* p_mtx = mtx;

	T* data_out = new T[size];
	memset(data_out, 0, size);

	for (row = pixels; row<_height; row++)
	{
		data_out_row = data_out + (row*width) + pixels;
		for (col = 0; col<_width; col++)
		{
			// get matrix
			p_mtx = mtx;
			for (row2 = row - pixels; row2<row + pixels; row2++)
			{
				data_row = data + (row2*width) + col;
				for (col2 = 0; col2<square_width; col2++)
				{
					*p_mtx++ = *(data_row)++;
				}
			}
			std::qsort(mtx, square_size, sizeof(T), compare_ascending<T>);
			*data_out_row++ = mtx[middle];
		}
	}
	delete[] mtx;
	return data_out;
}


} // namespace proimage
