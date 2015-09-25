/**********************************************************************************\
	Effect_Math.h
	
	Arithmetic and other math functions for Matrices
\**********************************************************************************/

#ifndef __EFFECT_MATH_H__
#define __EFFECT_MATH_H__

#include "constrain.h"
#include <cmath>

namespace imgeffects
{

/*----------------------------------------*\
	unsigned char* sum(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp);

	bpp := bits per pixel
	Returns a new Buffer, must be deleted
\*----------------------------------------*/
unsigned char* math_sum(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp);

/*----------------------------------------*\
unsigned char* sub(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp);

bpp := bits per pixel
Returns a new Buffer, must be deleted
\*----------------------------------------*/
unsigned char* math_sub(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp);

/*----------------------------------------*\
	unsigned char* mul_sqrt(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp);

	bpp := bits per pixel
	Apply Picture, sqrt(P1*P2)
	Returns a new Buffer, must be deleted
\*----------------------------------------*/
unsigned char* math_mul_sqrt(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp);


/*----------------------------------------*\
	unsigned char* pow2_add_sqrt(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp);

	bpp := bits per pixel
	Apply Picture, sqrt(P1^2+P2^2)
	Returns a new Buffer, must be deleted
\*----------------------------------------*/
unsigned char* math_pow2_sqrt(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp);


/**========================================================================================================================**\
	Math Template Functions
\**========================================================================================================================**/

template <typename T, typename T_out>
T_out* math_calc_T(T* Buff1, T* Buff2, size_t size, T_out(*func)(T, T))
{
	T_out* pOut = new T_out[size];
	T_out* _pOut = pOut;
	for (size_t i = 0; i<size; i++)
	{
		*_pOut++ = func(*Buff1++, *Buff2++);
	}
	return pOut;
}

template <typename T, typename T_out>
inline T_out add_T(T a, T b)
{
	return (T_out)constrain<T_out, T_out>(T_out(a) + b, 0, (T_out)~0);
}

template <typename T_out>
T_out* math_sum_T(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp)
{
	size_t size = (size_t)width*height;
	switch (bpp)
	{
	case 8:
		return math_calc_T<unsigned char, T_out>(Buff1, Buff2, size, add_T<unsigned char, T_out>);
	case 16:
		return math_calc_T<unsigned short, T_out>((unsigned short*)Buff1, (unsigned short*)Buff2, size, add_T<unsigned short, T_out>);
	}
	return 0;
}

template <typename T, typename T_out>
inline T_out sub_T(T a, T b)
{
	return (T_out)constrain<T_out, T_out>(T_out(a) - b, 0, (T_out)~0);
}

// Apply sqrt(P1^2+P2^2)
template <typename T, typename T_out>
inline T_out pow2_sqrt_T(T a, T b)
{
	double mulrt = sqrt((double(a)*a) + (double(b)*b));
	return T_out(mulrt + 0.5);
}

// Apply sqrt(P1*P2)
template <typename T, typename T_out>
inline T_out mul_sqrt_T(T a, T b)
{
	return T_out(sqrt(double(a)*b) + 0.5);
}


} // namespace ImageEffects

#endif // #ifndef __EFFECT_MATH_H__