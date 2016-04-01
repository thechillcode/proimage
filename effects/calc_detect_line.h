/**********************************************************************************\
	Algorithm_AlignImage.h
	
	Align an image horizontally / vertically
\**********************************************************************************/

#ifndef __Algorithm_AlignImage_H__
#define __Algorithm_AlignImage_H__

namespace proimage
{

/*----------------------------------------*\
	void DetectHorizontalLineTop_Slope_Mono8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* linepos, double* slope, size_t len);

	On an MONO8 or GRAY8 image the function tries to find the best line mathing the criteria.
	Searches from top to bottom.
	If direction is 'p' then searches from black to white, positive slope
	If direction is 'n' then searches from white to black, negative slope
	slope width is the amount of pixels distance used to cal the slope

	linepos is a pointer to an int buffer
	sloped is a pointer to an double buffer
	len is the length of both, buffers have to have the same length

	Returns found mathing line (is number of pixels counted from the middle of the image (+ -> right, - <- left), and slope.
	Slope is calulated as (sum(line1)-sum(line2)) / width, therefore slope is min -255 or max 255
	If slope is zero then no best match was found.
\*----------------------------------------*/
void DetectHorizontalLineTop_Slope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* linepos, double* slope, size_t len);
void DetectVerticalLineLeft_Slope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* columnpos, double* slope, size_t len);
void DetectHorizontalLineBottom_Slope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* linepos, double* slope, size_t len);
void DetectVerticalLineRight_Slope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* columnpos, double* slope, size_t len);

/*----------------------------------------*\
	void DetectHorizontalLine_Pattern_Mono8(unsigned char* Data, unsigned int width, unsigned int height, int* pattern, size_t patsize, int* linepos, double* match, size_t len);

	On an MONO8 or GRAY8 image the function tries to find the best line mathing the criteria.
	Searches from top to bottom.
	pattern is an int buffer, with values between 0,255 (values of desired pattern), use -1 to mask out lines

	linepos is a pointer to an int buffer
	match is a pointer to an double buffer
	len is the length of both, buffers have to have the same length

	Returns found mathing line (is number of pixels counted from the middle of the image (+ -> right, - <- left), and match.
	The best match is in the first buffer entrie 0.
	If match is zero then no match was found.
\*----------------------------------------*/
void DetectHorizontalLine_Pattern_Ch8(unsigned char* Data, unsigned int width, unsigned int height, int* pattern, size_t patsize, int* linepos, double* match, size_t len);
void DetectVerticalLine_Pattern_Ch8(unsigned char* Data, unsigned int width, unsigned int height, int* pattern, size_t patsize, int* columnpos, double* match, size_t len);

/*----------------------------------------*\
	float DetectAngularLineTop_BestSlope_Mono8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, char direction, unsigned int slopewidth, unsigned int* line, double* slope)

	On an MONO8 or GRAY8 image the function tries to find the best line mathing the criteria.
	Searches from top to bottom.
	slope width is the amount of pixels distance used to cal the slope

	Returns found mathing line, and slope. linepos or columnpos are position found relative to the center of the image
	Slope is calulated as (sum(line1)-sum(line2)) / width, therefore slope is min -255 or max 255
	If slope is zero then no best match was found.
	line represents the coordinate of the line, line is zero based
	Returna also bets found angle according to best slope found
\*----------------------------------------*/
float DetectAngularLineTop_BestSlope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, char direction, unsigned int slopewidth, int* linepos, double* slope);
float DetectAngularLineLeft_BestSlope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int percision, char direction, unsigned int slopewidth, int* columnpos, double* slope);
float DetectAngularLineBottom_BestSlope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int percision, char direction, unsigned int slopewidth, int* linepos, double* slope);
float DetectAngularLineRight_BestSlope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int percision, char direction, unsigned int slopewidth, int* columnpos, double* slope);

/*----------------------------------------*\
	float DetectAngularLineTop_BestPattern_Mono8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, int* pattern, size_t patsize, int* linepos, double* match);

	On an MONO8 or GRAY8 image the function tries to find the best line mathing the pattern.
	Searches from top to bottom.
	slope width is the amount of pixels distance used to cal the slope

	Returns found mathing line, and slope. linepos or columnpos are position found relative to the center of the image
	If match is zero then no best match was found.
	Returna also bets found angle according to best match found
\*----------------------------------------*/
float DetectHorizontalAngularLine_BestPattern_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, int* pattern, size_t patsize, int* linepos, double* match);
float DetectVerticalAngularLine_BestPattern_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, int* pattern, size_t patsize, int* columnpos, double* match);

} // namespace ImageEffects


#endif // #ifndef __Algorithm_AlignImage_H__