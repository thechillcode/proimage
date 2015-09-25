/**========================================================================================================================**\
	transform_translation.h


\**========================================================================================================================**/


#ifndef __TRANSFORM_TRANSLATION__
#define __TRANSFORM_TRANSLATION__

namespace imgeffects
{

	/*--------------------------------------------------------------------------------*\
		unsigned char* translate(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, unsigned int* new_width, unsigned int* new_height);

		Info text
	\*--------------------------------------------------------------------------------*/
	unsigned char* translate(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double x, double y, unsigned int* new_width, unsigned int* new_height);


	/*--------------------------------------------------------------------------------*\
	unsigned char* translate(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, unsigned int* new_width, unsigned int* new_height);

	Info text
	\*--------------------------------------------------------------------------------*/
	unsigned char* translate(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, unsigned int x, unsigned int y, unsigned int* new_width, unsigned int* new_height);

} // namespace imgeffects

#endif // #ifndef __TRANSFORM_TRANSLATION__