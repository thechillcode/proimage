/**********************************************************************************\
	filter_normalize.h
	
	Normalize an image
\**********************************************************************************/

#ifndef __FILTER_NORMALIZE__
#define __FILTER_NORMALIZE__

namespace imgeffects
{

/*----------------------------------------*\
	unsigned char* normalize(unsigned char* Data, unsigned int width, unsigned int height, unsigned int bpp)

	bpp := number of bits per pixel
	Normalize an image.
	Return a new buffer allocated with new
\*----------------------------------------*/
unsigned char* normalize_linear(unsigned char* Data, unsigned int width, unsigned int height, unsigned int bpp);

void normalize_linear_update(unsigned char* Data, unsigned int width, unsigned int height, unsigned int bpp);

} // namespace ImageEffects

#endif // #ifndef __FILTER_NORMALIZE__