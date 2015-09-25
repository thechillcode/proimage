/**========================================================================================================================**\
	transform_scaling.h


\**========================================================================================================================**/


#ifndef __TRANSFORM_SCALING__
#define __TRANSFORM_SCALING__

namespace imgeffects
{

	/*--------------------------------------------------------------------------------*\
		unsigned char* scale(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double fact_x, double fact_y, unsigned int* new_width, unsigned int* new_height);

		Info text
	\*--------------------------------------------------------------------------------*/
	unsigned char* scale(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double fact_x, double fact_y, unsigned int* new_width, unsigned int* new_height);

} // namespace imgeffects

#endif // #ifndef __TRANSFORM_SCALING__