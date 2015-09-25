/**********************************************************************************\
	Algorithm_Threshold_Otzu.h
	
	Alogrithm Otzu, to detect Gray Threshold
\**********************************************************************************/

namespace imgeffects
{

/*----------------------------------------*\
	int Algo_Otzu_8(unsigned char* buffer, unsigned int width, unsigned int height)

	Get a suggested threshold via Otzu Algo
	http://de.wikipedia.org/wiki/Schwellwertverfahren
	http://www.gomatlab.de/otsu-verfahren-bitte-um-hilfe-t16276.html
	
	Calc Otzu for 8 bit / 16 bit grayscale
\*----------------------------------------*/
size_t calc_threshold_otzu(unsigned char* buffer, unsigned int width, unsigned int height, unsigned int bpp);

} // namespace ImageEffects
