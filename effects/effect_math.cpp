/**********************************************************************************\
	Effect_Math.cpp
\**********************************************************************************/

#include "effect_math.h"

namespace proimage
{
	unsigned char* math_sum(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp)
	{
		size_t size = (size_t)width*height;
		switch (bpp)
		{
		case 8:
			return (unsigned char*)math_calc_T<unsigned char, unsigned char>(Buff1, Buff2, size, add_T<unsigned char, unsigned char>);
		case 16:
			return (unsigned char*)math_calc_T<unsigned short, unsigned short>((unsigned short*)Buff1, (unsigned short*)Buff2, size, add_T<unsigned short, unsigned short>);
		}
		return 0;
	}

	unsigned char* math_sub(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp)
	{
		size_t size = (size_t)width*height;
		switch (bpp)
		{
		case 8:
			return (unsigned char*)math_calc_T<unsigned char, unsigned char>(Buff1, Buff2, size, sub_T<unsigned char, unsigned char>);
		case 16:
			return (unsigned char*)math_calc_T<unsigned short, unsigned short>((unsigned short*)Buff1, (unsigned short*)Buff2, size, sub_T<unsigned short, unsigned short>);
		}
		return 0;
	}

	unsigned char* math_pow2_sqrt(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp)
	{
		size_t size = (size_t)width*height;
		switch (bpp)
		{
		case 8:
			return (unsigned char*)math_calc_T<unsigned char, unsigned char>(Buff1, Buff2, size, pow2_sqrt_T<unsigned char, unsigned char>);
		case 16:
			return (unsigned char*)math_calc_T<unsigned short, unsigned short>((unsigned short*)Buff1, (unsigned short*)Buff2, size, pow2_sqrt_T<unsigned short, unsigned short>);
		}
		return 0;
	}

	unsigned char* math_mul_sqrt(unsigned char* Buff1, unsigned char* Buff2, unsigned int width, unsigned int height, unsigned int bpp)
	{
		size_t size = (size_t)width*height;
		switch (bpp)
		{
		case 8:
			return (unsigned char*)math_calc_T<unsigned char, unsigned char>(Buff1, Buff2, size, mul_sqrt_T<unsigned char, unsigned char>);
		case 16:
			return (unsigned char*)math_calc_T<unsigned short, unsigned short>((unsigned short*)Buff1, (unsigned short*)Buff2, size, mul_sqrt_T<unsigned short, unsigned short>);
		}
		return 0;
	}

	/*----------------------------------------*\
	T* math_t_overlay(T* Buff1, unsigned int width, unsigned int height, T* Buff2, unsigned int x, unsigned int y, unsigned int w, unsigned int h)

	Add a smaller image into a bigger image
	Returns a new Buffer, must be deleted
	\*----------------------------------------*/
	template <class T>
	T* math_t_overlay(T* Buff1, unsigned int width, unsigned int height, T* Buff2, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
	{
		if ((y + h) > height) return 0;
		if ((x + w) > width) return 0;
		size_t size = size_t(width)*height;
		T* pCalc = new T[size];
		memcpy(pCalc, Buff1, size);
		T* _pCalc = pCalc;
		T min = 0;
		T max = ~0;
		unsigned int sum = 0;
		unsigned int i = 0, j = 0;
		unsigned int _h = y + h;
		for (j = y; j<_h; j++)
		{
			_pCalc = pCalc + (j*w) + x;
			for (i = 0; i<w; i++)
			{
				sum = *_pCalc + *Buff2++;
				*_pCalc++ = constrain(sum, min, max);
			}
		}
		return pCalc;
	}

} // namespace ImageEffects
