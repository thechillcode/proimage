/**========================================================================================================================**\
	transform_scaling.h


\**========================================================================================================================**/


#ifndef __TRANSFORM_SHEAR__
#define __TRANSFORM_SHEAR__

namespace imgeffects
{

	/*--------------------------------------------------------------------------------*\
		unsigned char* scale(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double fact_x, double fact_y, unsigned int* new_width, unsigned int* new_height);

		Info text
	\*--------------------------------------------------------------------------------*/
	unsigned char* shear_x(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double shear_x, unsigned int* new_width, unsigned int* new_height);
	unsigned char* shear_y(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, double shear_y, unsigned int* new_width, unsigned int* new_height);

} // namespace imgeffects

#endif // #ifndef __TRANSFORM_SCALING__