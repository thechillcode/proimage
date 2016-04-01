/**========================================================================================================================**\
	Transform Matrix
\**========================================================================================================================**/

#ifndef __TRANSFORM__
#define __TRANSFORM__

#include "TransformMatrix.h"

namespace proimage
{
	/*--------------------------------------------------------------------------------*\
	unsigned char*  transform(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, TransformMatrix* tm, unsigned int* new_width, unsigned int* new_height)

	Info text
	\*--------------------------------------------------------------------------------*/
	unsigned char*  transform(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, TransformMatrix* tm, unsigned int* new_width, unsigned int* new_height);
}


#endif // #ifndef __TRANSFORM__