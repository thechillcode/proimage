/**********************************************************************************\
	Effect_ConvolutionMatrix.cpp
	
	Apply Convolution Matrix to Image Buffer
\**********************************************************************************/

#include "filter_convolute.h"
#include <malloc.h>

namespace proimage
{

ConvolutionMatrix::ConvolutionMatrix()
{
}
ConvolutionMatrix::~ConvolutionMatrix()
{
	clear();
}

void ConvolutionMatrix::clear()
{
	for (size_t i = 0; i < num_matrices(); i++)
	{
		delete[] MatrixData[i].pData;
	}
	MatrixData.clear();
}

size_t ConvolutionMatrix::num_matrices()
{
	return MatrixData.size();
}

ConvolutionMatrix::ConvolutionMatrixData* ConvolutionMatrix::get_matrix(size_t pos)
{
	if (pos < num_matrices())
	{
		return &(MatrixData[pos]);
	}
	return NULL;
}

void ConvolutionMatrix::add(int* pData, unsigned int width, unsigned int height, int divisor, int offset)
{

	size_t len = size_t(width)*height;
	int* p = new int[len];
	memcpy(p, pData, len*4);
	MatrixData.push_back({ p, width, height, divisor, offset });
}

void ConvolutionMatrix::remove(size_t pos)
{
	if (pos < num_matrices())
	{
		delete[] MatrixData[pos].pData;
		MatrixData.erase(MatrixData.begin() + pos);
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
