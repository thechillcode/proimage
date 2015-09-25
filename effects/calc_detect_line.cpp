/**********************************************************************************\
	Algorithm_DetectLine.h
	
	Detect a horizontal line, through rotation also vertically and angular lines
\**********************************************************************************/

#include "calc_detect_line.h"
#include "transform_rotation.h"

#define ABS(x) (x < 0 ? -x : x)
#define ABSDIFF(a,b) (a < b ? (b-a) : (a-b))
#define ROUNDUINT(x) unsigned int(x + 0.5)

namespace imgeffects
{

/**********************************************************************************\
	Detect Slope

	Slope ist der abstand zwischen 2  linien
\**********************************************************************************/
void DetectHorizontalLineTop_Slope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* linepos, double* slope, size_t len)
{
	long long sumline1=0,sumline2=0;
	unsigned int center_line = ROUNDUINT((double(height)/2))-1;
	double curSlope = 0;
	int shift_pos = -1;
	unsigned int i=0,i2=0,i3 = 0;
	unsigned int j = 0;
	unsigned char* pLine = Data;
	// Get all slopes
	long long* pSumWidth = new long long[height];
	for (i2=0; i2<len; i2++)
	{
		linepos[i2] = 0;
		slope[i2] = 0;
	}
	// Only run through needed lines
	for (j=0; j<height; j++)
	{
		pSumWidth[j]=0;
		for (i=0; i<width; i++)
		{
			pSumWidth[j] += *pLine++;
		}
	}
	// Only run through needed lines
	for (j=0; j<(height-slopewidth); j++)
	{
		sumline1=pSumWidth[j];
		sumline2=pSumWidth[j+slopewidth];
		// Check Slope
		curSlope = double(sumline2-sumline1)/width;
		shift_pos = -1;
		// Positive Slope required
		if (direction == 'p')
		{
			for (i2=0; i2<len; i2++)
			{
				if (curSlope > slope[i2])
				{
					shift_pos = i2;
					break;
				}
			}
		}
		// Negative Slope required
		else if (direction == 'n')
		{
			for (i2=0; i2<len; i2++)
			{
				if (curSlope < slope[i2])
				{
					shift_pos = i2;
					break;
				}
			}
		}
		if (shift_pos != -1)
		{
			// shift one down
			for (i3=shift_pos+1; i3<len; i3++)
			{
				slope[i3] = slope[i3-1];
				linepos[i3] = linepos[i3-1];
			}
			slope[shift_pos] = curSlope;
			// calc from center if image
			linepos[shift_pos] = (j+slopewidth)-center_line;
		}
	}
	delete [] pSumWidth;
}

void DetectVerticalLineLeft_Slope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* columnpos, double* slope, size_t len)
{
	// Rotate Image
	unsigned char* rotimg = rotate_270(Data, width, height, 8);
	DetectHorizontalLineTop_Slope_Ch8(rotimg, height, width, direction, slopewidth, columnpos, slope, len);
	delete [] rotimg;
	// No Conversion Needed
}

void DetectHorizontalLineBottom_Slope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* linepos, double* slope, size_t len)
{
	// Rotate Image
	unsigned char* rotimg = rotate_180(Data, width, height, 8);
	DetectHorizontalLineTop_Slope_Ch8(rotimg, width, height, direction, slopewidth, linepos, slope, len);
	delete [] rotimg;
	// Convert Back
	for (unsigned int i=0; i<len; i++)
	{
		linepos[i] = -linepos[i];
	}
}

void DetectVerticalLineRight_Slope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, char direction, unsigned int slopewidth, int* columnpos, double* slope, size_t len)
{
	// Rotate Image
	unsigned char* rotimg = rotate_90(Data, width, height, 8);
	DetectHorizontalLineTop_Slope_Ch8(rotimg, height, width, direction, slopewidth, columnpos, slope, len);
	delete [] rotimg;
	// Convert Back
	for (unsigned int i=0; i<len; i++)
	{
		columnpos[i] = -columnpos[i];
	}
}

/**********************************************************************************\
	Detect Pattern
\**********************************************************************************/
void DetectHorizontalLine_Pattern_Ch8(unsigned char* Data, unsigned int width, unsigned int height, int* pattern, size_t patsize, int* linepos, double* match, size_t len)
{
	double sumline1=0;
	unsigned int center_line = ROUNDUINT((double(height)/2))-1;
	double curMatch = 0;
	unsigned int i=0,i2=0,i3 = 0;
	unsigned int j = 0;
	unsigned char* pLine = Data;
	// Get all slopes
	double* pSumWidth = new double[height];
	for (i2=0; i2<len; i2++)
	{
		linepos[i2] = 0;
		match[i2] = 0;
	}
	unsigned int patcount = 0;
	for (i2=0; i2<patsize; i2++)
	{
		if (pattern[i2] != -1) patcount++;
	}
	// Only run through needed lines
	for (j=0; j<height; j++)
	{
		pSumWidth[j]=0;
		for (i=0; i<width; i++)
		{
			pSumWidth[j] += *pLine++;
		}
		pSumWidth[j] /= width; // Norm between [0,255]
	}
	// Only run through needed lines
	for (j=0; j<(height-patsize); j++)
	{
		curMatch = 0;
		for (i=0; i<patsize; i++)
		{
			if (pattern[i] != -1)
			{
				sumline1 = pSumWidth[j+i];
				curMatch += ABSDIFF(sumline1, pattern[i]);
			}
		}
		// Calc matching percentage
		curMatch /= patcount;
		curMatch /= 0xFF;
		curMatch = 100*(1-curMatch);
		for (i2=0; i2<len; i2++)
		{
			if (curMatch > match[i2])
			{
				// shift one down
				for (i3=i2+1; i3<len; i3++)
				{
					match[i3] = match[i3-1];
					linepos[i3] = linepos[i3-1];
				}
				match[i2] = curMatch;
				// calc from center if image
				linepos[i2] = j-center_line;
				break;
			}
		}
	}
	delete [] pSumWidth;
}

void DetectVerticalLine_Pattern_Ch8(unsigned char* Data, unsigned int width, unsigned int height, int* pattern, size_t patsize, int* columnpos, double* match, size_t len)
{
	// Rotate Image
	unsigned char* rotimg = rotate_270(Data, width, height, 8);
	DetectHorizontalLine_Pattern_Ch8(rotimg, height, width, pattern, patsize, columnpos, match, len);
	delete [] rotimg;
	// No Conversion Needed
}

/**********************************************************************************\
	Detect angular Line Best Slope
\**********************************************************************************/
float DetectAngularLineTop_BestSlope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, char direction, unsigned int slopewidth, int* linepos, double* slope)
{
	// Search Angle
	anglcc = ABS(anglcc);
	anglcw = -(ABS(anglcw));
	float angle = 0;
	float bestangle = 0;
	double bestslope = 0;
	int bestline = 0;
	// Only get best slope per angle
	double _slope[1] = {0};
	double _absslope = 0;
	int _line[1] = {0};
	unsigned int new_width=0, new_height=0;
	unsigned char* rotimg = 0;
	// Go through all angles
	for (angle=anglcw; angle<=anglcc; angle += 1)
	{
		rotimg = rotate(Data, width, height, 8, angle, 0,0, &new_width, &new_height);
		DetectHorizontalLineTop_Slope_Ch8(rotimg, new_width, new_height, direction, slopewidth, (int*)_line, (double*)_slope, 1);
		delete [] rotimg;
		if (ABS(_slope[0]) > _absslope)
		{
			_absslope = ABS(_slope[0]);
			bestslope = _slope[0];
			bestline = _line[0];
			bestangle = angle;
		}
	}
	// precision start and end
	float ppoint=1.0,angstart=0,angstop=0;
	for (unsigned int i=0; i<precision; i++)
	{
		ppoint *= 0.1f;
		angstart = bestangle - 9*ppoint;
		angstop = bestangle + 9*ppoint;
		for (angle=angstart; angle<=angstop; angle += ppoint)
		{
			rotimg = rotate(Data, width, height, 8, angle, 0,0, &new_width, &new_height);
			DetectHorizontalLineTop_Slope_Ch8(rotimg, new_width, new_height, direction, slopewidth, (int*)_line, (double*)_slope, 1);
			delete [] rotimg;
			if (ABS(_slope[0]) > _absslope)
			{
				_absslope = ABS(_slope[0]);
				bestslope = _slope[0];
				bestline = _line[0];
				bestangle = angle;
			}
		}
	}
	*linepos = bestline;
	*slope = bestslope;
	return bestangle;
}

float DetectAngularLineLeft_BestSlope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, char direction, unsigned int slopewidth, int* columnpos, double* slope)
{
	double _slope = 0;
	int _line = 0;
	float _angle = 0;
	// Rotate Image
	unsigned char* rotimg = rotate_270(Data, width, height, 8);
	_angle = DetectAngularLineTop_BestSlope_Ch8(rotimg, height, width, anglcc, anglcw, precision, direction, slopewidth, &_line, &_slope);
	delete [] rotimg;
	// Convert Back
	*columnpos = _line;
	*slope = _slope;
	return _angle;
}

float DetectAngularLineBottom_BestSlope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, char direction, unsigned int slopewidth, int* linepos, double* slope)
{
	double _slope = 0;
	int _line = 0;
	float _angle = 0;
	
	// Rotate Image
	unsigned char* rotimg = rotate_180(Data, width, height, 8);
	_angle = DetectAngularLineTop_BestSlope_Ch8(rotimg, width, height, anglcc, anglcw, precision, direction, slopewidth, &_line, &_slope);
	delete [] rotimg;

	// Convert Back
	*linepos = -_line;
	*slope = _slope;
	return _angle;
}

float DetectAngularLineRight_BestSlope_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, char direction, unsigned int slopewidth, int* columnpos, double* slope)
{
	double _slope = 0;
	int _line = 0;
	float _angle = 0;
	
	// Rotate Image
	unsigned char* rotimg = rotate_90(Data, width, height, 8);
	_angle = DetectAngularLineTop_BestSlope_Ch8(rotimg, height, width, anglcc, anglcw, precision, direction, slopewidth, &_line, &_slope);
	delete [] rotimg;

	// Convert Back
	*columnpos = -_line;
	*slope = _slope;
	return _angle;
}

/**********************************************************************************\
	Detect angular Line Best Pattern
\**********************************************************************************/
float DetectHorizontalAngularLine_BestPattern_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, int* pattern, size_t patsize, int* linepos, double* match)
{
	// Search Angle
	anglcc = ABS(anglcc);
	anglcw = -(ABS(anglcw));
	float angle = 0;
	float bestangle = 0;
	double bestmatch = 0;
	int bestline = 0;
	// Only get best slope per angle
	double _match[1] = {0};
	int _line[1] = {0};
	unsigned int new_width=0, new_height=0;
	unsigned char* rotimg = 0;
	// Go through all angles
	for (angle=anglcw; angle<=anglcc; angle += 1)
	{
		rotimg = rotate(Data, width, height, 8, angle, 0,0, &new_width, &new_height);
		DetectHorizontalLine_Pattern_Ch8(rotimg, new_width, new_height, pattern, patsize, (int*)_line, (double*)_match, 1);
		delete [] rotimg;
		if (_match[0] > bestmatch)
		{
			bestmatch = _match[0];
			bestline = _line[0];
			bestangle = angle;
		}
	}
	// precision start and end
	float ppoint=1.0,angstart=0,angstop=0;
	for (unsigned int i=0; i<precision; i++)
	{
		ppoint *= 0.1f;
		angstart = bestangle - 9*ppoint;
		angstop = bestangle + 9*ppoint;
		for (angle=angstart; angle<=angstop; angle += ppoint)
		{
			rotimg = rotate(Data, width, height, 8, angle, 0,0, &new_width, &new_height);
			DetectHorizontalLine_Pattern_Ch8(rotimg, new_width, new_height, pattern, patsize, (int*)_line, (double*)_match, 1);
			delete [] rotimg;
			if (_match[0] > bestmatch)
			{
				bestmatch = _match[0];
				bestline = _line[0];
				bestangle = angle;
			}
		}
	}
	*linepos = bestline;
	*match = bestmatch;
	return bestangle;
}

float DetectVerticalAngularLine_BestPattern_Ch8(unsigned char* Data, unsigned int width, unsigned int height, float anglcc, float anglcw, unsigned int precision, int* pattern, size_t patsize, int* columnpos, double* match)
{
	double _match = 0;
	int _line = 0;
	float _angle = 0;
	// Rotate Image
	unsigned char* rotimg = rotate_270(Data, width, height, 8);
	_angle = DetectHorizontalAngularLine_BestPattern_Ch8(rotimg, height, width, anglcc, anglcw, precision, pattern, patsize, &_line, &_match);
	delete [] rotimg;
	// Convert Back
	*columnpos = _line;
	*match = _match;
	return _angle;
}

} // namespace ImageEffects
