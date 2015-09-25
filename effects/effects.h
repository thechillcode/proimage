/****************************************************************************************************************************\
 *	effects.h

 *	Load All Effect Headers
 *	All Effects only handle single channels/layers, e.g. single colors or gray scale, as 8bit or 16 bit
\****************************************************************************************************************************/

#ifndef __EFFECTHEADERS__
#define __EFFECTHEADERS__

// Alogrithms
//#include "Algorithm_DetectLine.h"
// Effects

#include "Effect_FormatConversion.h"
#include "effect_math.h"

// Calculation
#include "calc_threshold.h"
#include "calc_histogram.h"

// Filters
#include "filter_convolute.h"
#include "filter_blur.h"
#include "filter_edgedetection.h"
#include "filter_invert.h"
#include "filter_median.h"
#include "filter_normalize.h"
#include "filter_sharpen.h"

// Transformation
#include "transform_matrix.h"
#include "transform_rotation.h"
#include "transform_scaling.h"
#include "transform_shear.h"
#include "transform_crop.h"


#endif // #ifndef __EFFECTALLHEADERS_H__