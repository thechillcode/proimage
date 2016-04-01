/**========================================================================================================================**\
	Effect_InvertImage.h

	Inverts the image e.g. px = ~px;
\**========================================================================================================================**/

#ifndef __EFFECT_INVERTIMAGE_H__
#define __EFFECT_INVERTIMAGE_H__

namespace proimage
{

/*--------------------------------------------------------------------------------*\
	unsigned char* invert (unsigned char* data, unsigned int width, unsigned int height, unsigned int bpp);

	inverts the image
	returns a new allocated image.
\*--------------------------------------------------------------------------------*/
unsigned char* invert(unsigned char* data, unsigned int width, unsigned int height, unsigned int bpp);

void invert_update(unsigned char* data, unsigned int width, unsigned int height, unsigned int bpp);

} // namespace proimage

#endif // #ifndef __EFFECT_INVERTIMAGE_H__