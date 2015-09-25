/**********************************************************************************\
	Effect_ConvolutionMatrix.cpp
	
	Apply Convolution Matrix to Image Buffer
\**********************************************************************************/

#include "filter_convolute.h"
#include <malloc.h>

namespace imgeffects
{

ConvolutionMatrix::ConvolutionMatrix()
{
	pMatrixData = 0;
	matrices = 0;
}
ConvolutionMatrix::~ConvolutionMatrix()
{
	clear();
}

void ConvolutionMatrix::clear()
{
	if (pMatrixData)
	{
		for (unsigned int i = 0; i<matrices; i++)
		{
			delete[] pMatrixData[i].pData;
		}
		free((void*)pMatrixData);
	}
	pMatrixData = 0;
	matrices = 0;
}

void ConvolutionMatrix::add(int* pData, unsigned int width, unsigned int height, int divisor, int offset)
{
	matrices++;
	pMatrixData = (ConvolutionMatrixData*)realloc((void*)pMatrixData, sizeof(ConvolutionMatrixData)*matrices);
	unsigned int pos = matrices-1;
	size_t len = size_t(width)*height;
	pMatrixData[pos].pData = new int[len];
	memcpy(pMatrixData[pos].pData, pData, len*4);
	pMatrixData[pos].width = width;
	pMatrixData[pos].height = height;
	pMatrixData[pos].divisor = divisor;
	pMatrixData[pos].offset = offset;
}

void ConvolutionMatrix::remove(unsigned int pos)
{
	if (pos < matrices)
	{
		delete[] pMatrixData[pos].pData;
		for (unsigned int i=pos+1; i<matrices; i++)
		{
			pMatrixData[i-1] = pMatrixData[i];
		}
		matrices--;
		pMatrixData = (ConvolutionMatrixData*)realloc((void*)pMatrixData, sizeof(ConvolutionMatrixData)*matrices);
	}
}


unsigned char* convolute(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, ConvolutionMatrix*  ConvMatrix)
{
	switch (bpp)
	{
	case 8:
		return convolute_T(pBuff, width, height, ConvMatrix);
	case 16:
		return (unsigned char*)convolute_T((unsigned short*)pBuff, width, height, ConvMatrix);
	}
	return 0;
}

} // namespace ImageEffects
