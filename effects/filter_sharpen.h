/**********************************************************************************\
	filer_sharpen.h
\**********************************************************************************/

#ifndef __FILTER_SHARPEN__
#define __FILTER_SHARPEN__

namespace imgeffects
{
/*--------------------------------------------------------------------------------*\
	unsigned char* sharpen_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double sharpsigma, int sharpwidth)

	bpp := Bits Per Pixel
	Blurs an image with given parameters
	Returns a new buffer, must be deleted
\*--------------------------------------------------------------------------------*/
unsigned char* sharpen_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius, double sigma);

/*--------------------------------------------------------------------------------*\
	unsigned char* sharpen_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius);

	bpp := Bits Per Pixel
	Blurs an image with given parameters
	Returns a new buffer, must be deleted
\*--------------------------------------------------------------------------------*/
unsigned char* sharpen_gauss(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, int radius);

} // namespace ImageEffects

#endif // #ifndef __FILTER_SHARPEN__