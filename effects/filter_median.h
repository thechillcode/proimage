/**========================================================================================================================**\
	Effect_MediaFilter.h

	Implementation of a median filter
\**========================================================================================================================**/

#ifndef __FILTER_MEDIAN__
#define __FILTER_MEDIAN__

namespace imgeffects
{

/*--------------------------------------------------------------------------------*\
	unsigned char* median_filter (unsigned char* data, unsigned int width, unsigned int height, unsigned int bpp, unsigned int radius)

	radius := is the amount of sourouding pixels, e.g. 1 = 3x3 matrix, 3 = 7x7 matrix
\*--------------------------------------------------------------------------------*/
unsigned char* median_filter (unsigned char* data, unsigned int width, unsigned int height, unsigned int bpp, unsigned int radius);


} // namespace imgeffects

#endif // #ifndef __FILTER_MEDIAN__