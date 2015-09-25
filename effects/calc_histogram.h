/**========================================================================================================================**\
	calc_histogram.h
\**========================================================================================================================**/

#ifndef __CALC_HISTORGRAM__
#define __CALC_HISTORGRAM__

namespace imgeffects
{
	/*--------------------------------------------------------------------------------*\
	size_t* calc_histogram(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp, size_t* entries)

	calculates a histogram over all pixel values
	returns a "new" allocated double buffer, use "delete" to free buffer after usage
	\*--------------------------------------------------------------------------------*/
	size_t* calc_histogram(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp, size_t* entries);

	/*--------------------------------------------------------------------------------*\
		double* calc_histogram_width(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp)

		calculates a histogram over all pixels in one column, starting left ending right
		returns a "new" allocated double buffer, use "delete" to free buffer after usage

		double is in the range between 0 and 100, 1 all pixels were ~0, 0 all pixels were 0
	\*--------------------------------------------------------------------------------*/
	size_t* calc_histogram_width(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp);

	/*--------------------------------------------------------------------------------*\
		double* calc_histogram_height(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp)

		calculates a histogram over all pixels in one column, starting left ending right
		returns a "new" allocated double buffer, use "delete" to free buffer after usage
	\*--------------------------------------------------------------------------------*/
	size_t* calc_histogram_height(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp);

} // namespace ImageEffects

#endif // #ifndef __CALC_HISTORGRAM__