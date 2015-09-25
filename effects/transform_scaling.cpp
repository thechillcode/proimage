/**========================================================================================================================**\
	Transform Scaling
\**========================================================================================================================**/


/*--------------------------------------------------------------------------------*\
Function()

Info text
\*--------------------------------------------------------------------------------*/


#include "transform_scaling.h"
#include "transform_matrix.h"

namespace imgeffects
{
	unsigned char* scale(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double fact_x, double fact_y, unsigned int* new_width, unsigned int* new_height)
	{
		TransformMatrix tm;
		tm.add_scaling(fact_x, fact_y);
		return transform(pBuff, width, height, bpp, &tm, new_width, new_height);
	}

} // namespace imgeffects
