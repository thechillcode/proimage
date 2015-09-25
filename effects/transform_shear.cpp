/**========================================================================================================================**\
	Transform Scaling
\**========================================================================================================================**/


/*--------------------------------------------------------------------------------*\
Function()

Info text
\*--------------------------------------------------------------------------------*/


#include "transform_shear.h"
#include "transform_matrix.h"

#include <memory>
#define _USE_MATH_DEFINES
#include <math.h>

namespace imgeffects
{
	unsigned char* shear_x(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double shear_x, unsigned int* new_width, unsigned int* new_height)
	{
		TransformMatrix tm;
		tm.add_shear_x(shear_x);
		return transform(pBuff, width, height, bpp, &tm, new_width, new_height);
	}

	unsigned char* shear_y(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double shear_y, unsigned int* new_width, unsigned int* new_height)
	{
		TransformMatrix tm;
		tm.add_shear_y(shear_y);
		return transform(pBuff, width, height, bpp, &tm, new_width, new_height);
	}

} // namespace imgeffects
