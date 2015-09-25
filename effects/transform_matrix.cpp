/**========================================================================================================================**\
	Transform Matrix
\**========================================================================================================================**/


/*--------------------------------------------------------------------------------*\
Function()

Info text
\*--------------------------------------------------------------------------------*/

#include "transform_matrix.h"
#include "calc_bilinear.h"
#include <memory>

namespace imgeffects
{
	template<typename T>
	T* transform_T(T* pBuff, unsigned int width, unsigned int height, double invmx[3][3], T* pout, unsigned int new_width, unsigned int new_height)
	{
		//double invmx[3][3] = { 0 };
		//tm->get_invmatrix(invmx);

		T* p = pout;
		unsigned int i = 0, j = 0;
		double opix_x = 0, opix_y = 0;
		// Parse Buffer
		for (j = 0; j<new_height; j++)
		{
			for (i = 0; i<new_width; i++)
			{
				// Vector i,j
				// Calc position in original image
				opix_x = (invmx[0][0] * i) + (invmx[0][1] * j) + invmx[0][2];
				opix_y = (invmx[1][0] * i) + (invmx[1][1] * j) + invmx[1][2];

				*p++ = calc_bilinear_value(pBuff, width, height, opix_x, opix_y);
			}
		}
		return pout;
	}

	unsigned char* transform(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, TransformMatrix* tm, unsigned int* new_width, unsigned int* new_height)
	{
		int offset_x = 0;
		int offset_y = 0;
		tm->calc_newsize(tm->m_matrix, width, height, &offset_x, &offset_y, new_width, new_height);
		unsigned int w = *new_width;
		unsigned int h = *new_height;

		// add offset translation to invmatrix append
		double inv_trans[3][3] = {
			{ 1, 0, offset_x },
			{ 0, 1, offset_y },
			{ 0, 0, 1 },
		};
		double invers[3][3] = { 0 };
		tm->mul(tm->m_invmatrix, inv_trans, invers);
		//tm->add_invmatrix(inv_trans, true);

		// create new buffer
		size_t n = size_t(w)*h*bpp;
		unsigned char* new_buff = new unsigned char[n];
		memset((void*)new_buff, 0, n);

		switch (bpp)
		{
		case 8:
			return transform_T<unsigned char>(pBuff, width, height, invers, new_buff, w, h);
		case 16:
			return (unsigned char*)transform_T<unsigned short>((unsigned short*)pBuff, width, height, invers, (unsigned short*)new_buff, w, h);
		}
		return 0;
	}
}