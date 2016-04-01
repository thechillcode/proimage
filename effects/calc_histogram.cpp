/**********************************************************************************\
	calc_histogram.cpp
\**********************************************************************************/

#include "calc_histogram.h"
#include "calc_histogram_template.h"

namespace proimage
{

	size_t* calc_histogram(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp, size_t* entries)
	{
		switch (bpp)
		{
		case 8:
			return calc_histogram_T<unsigned char>(buffer, width, height, entries);
		case 16:
			return calc_histogram_T<unsigned short>((unsigned short*)buffer, width, height, entries);
		}
		return 0;
	}

	size_t* calc_histogram_width(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp)
	{
		switch (bpp)
		{
		case 8:
			return calc_histogram_width_T<unsigned char>(buffer, width, height);
		case 16:
			return calc_histogram_width_T<unsigned short>((unsigned short*)buffer, width, height);
		}
		return 0;
	}

	size_t* calc_histogram_height(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp)
	{
		switch (bpp)
		{
		case 8:
			return calc_histogram_height_T<unsigned char>(buffer, width, height);
		case 16:
			return calc_histogram_height_T<unsigned short>((unsigned short*)buffer, width, height);
		}
		return 0;
	}
} // namespace proimage
