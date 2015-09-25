/****************************************************************************************************************************\
 *	Effect_Defines.h
 ****************************************************************************************************************************/

#ifndef __EFFECTDEFINES_H__
#define __EFFECTDEFINES_H__

#define _USE_MATH_DEFINES
#include <cmath>


#define ABS(x) (x < 0 ? -x : x)
#define CONSTRAIN(x,min,max) (x < min ? min : (x > max ? max : x))
#define ABSDIFF(a,b) (a < b ? (b-a) : (a-b))
#define ROUNDINT(num) int(num+0.5)
//#define ANGLETORAD(angle) float((angle*M_PI)/180)

#define RADTODEG(rad) ((rad * 180) / M_PI)
#define DEGTORAD(deg) ((deg * M_PI) / 180)


#endif