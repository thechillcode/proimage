/**********************************************************************************\
Algorithm_Threshold_Otzu.cpp

Alogrithm Otzu, to detect Gray Threshold
\**********************************************************************************/

#include "calc_threshold.h"
#include "calc_threshold_template.h"

namespace proimage
{

	/*----------------------------------------*\
	Function()

	Get a suggested threshold via Otzu Algo
	http://de.wikipedia.org/wiki/Schwellwertverfahren
	http://www.gomatlab.de/otsu-verfahren-bitte-um-hilfe-t16276.html

	Calc Otzu for 8 bit grayscale
	\*----------------------------------------*/
	size_t calc_threshold_otzu(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp)
	{
		switch (bpp)
		{
		case 8:
			return (size_t)calc_threshold_otzu_T<unsigned char>(buffer, width, height);
		case 16:
			return (size_t)calc_threshold_otzu_T<unsigned short>((unsigned short*)buffer, width, height);
		}
		return -1;
	}

} // namespace proimage
