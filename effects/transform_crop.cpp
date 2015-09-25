/**********************************************************************************\
	Effect_Crop.cpp
\**********************************************************************************/

#include "transform_crop.h"
#include <memory>

namespace imgeffects
{

unsigned char* crop(unsigned char* Data, unsigned int width, unsigned int height, unsigned int bpp, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
	switch (bpp)
	{
	case 8:
		return crop_T(Data, width, height, x, y, w, h);
	case 16:
		return (unsigned char*)crop_T((unsigned short*)Data, width, height, x, y, w, h);
	}
	return 0;
}

} // namespace ImageEffects
