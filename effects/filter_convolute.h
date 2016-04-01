/**********************************************************************************\
	Effect_ConvolutionMatrix.h
	
	Apply Convolution Matrix to Image Buffer
\**********************************************************************************/

#ifndef __FILTER_CONVOLUTE__
#define __FILTER_CONVOLUTE__

#include "EFFECTS_DEFINES.h"
#include <vector>
#include <memory>


namespace proimage
{

/*----------------------------------------*\
	Convolution Matrix Class
\*----------------------------------------*/
class ConvolutionMatrix
{

public:
	// Convolution Matrix Struct
	struct ConvolutionMatrixData
	{
		int* pData;
		unsigned int width;
		unsigned int height;
		int divisor;
		int offset;
	};

private:
	std::vector<ConvolutionMatrixData> MatrixData;

public:
	ConvolutionMatrix();
	~ConvolutionMatrix();

	size_t num_matrices();

	ConvolutionMatrixData* get_matrix(size_t pos);
	void clear();
	void add(int* pData, unsigned int width, unsigned int height, int divisor, int offset);
	void remove(size_t pos);
};

/*----------------------------------------*\
	unsigned char* convolute(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, ConvolutionMatrix*  ConvMatrix)

	bpp := number of bits per pixel
	Each color channels is applied separately
	The side lengths of the matrices have to be unairy, e.g. 3x5, 3x3, 7x3, the matrix needs to have a center and of Type ConvolutionMatrix
	Applies a series or one convolution Matrix to the Buffer.
	Returns a new buffer, must be deleted
\*----------------------------------------*/
unsigned char* convolute(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, ConvolutionMatrix*  ConvMatrix);


/*----------------------------------------*\
	T_return* apply_convolution_matrix_template(T* pBuff, unsigned int width, unsigned int height, ConvolutionMatrixData* matrix)

	Each color channel is applied separately
	channels is number of color channels, gray = 1, rgb = 3
	Template to calc convolution Matrix, works for 8/16 bit Gray / RGB
	16 bit T pBuff has to be given as unsigned short*
	Returns a new Buffer (int*)
\*----------------------------------------*/
template <typename T, typename T_return>
T_return* apply_convolution_matrix_T(T* pBuff, unsigned int width, unsigned int height, ConvolutionMatrix::ConvolutionMatrixData* matrix)
{
	// bpp = bytes per pixel, or color channles per pixel
	int* pMatrix = matrix->pData;

	// Get longest destinantion to center
	int desthor = int(matrix->width / 2);
	int destver = int(matrix->height / 2);

	// Applying width and height, depending on distance to center
	unsigned int applw = 0, applh = 0;
	unsigned int startw = 0, starth = 0;
	unsigned int w = 0, h = 0;
	unsigned int stride = width;

	// Create Buffers
	size_t size = width*height;
	T_return* pBuffOut = new T_return[size];
	// Set dest buffer to zero
	memset((void*)pBuffOut, 0, (size*sizeof(T_return)));
	T_return* pOut = 0;
	T_return* pOutOffset = 0;
	T* pIn = 0;
	T* pInOffset = 0;

	// Parse through Matrix line by line
	// Apply urrent field to buffer pixel with destinantion from center
	int i = 0, j = 0;
	int abs_i = 0, abs_j = 0;
	int neg_desthor = -desthor;
	int neg_destver = -destver;
	int end_desthor = desthor + 1;
	int end_destver = destver + 1;
	for (j = neg_destver; j<end_destver; j++)
	{
		for (i = neg_desthor; i<end_desthor; i++)
		{
			int field = *pMatrix++;
			// only apply field if != 0
			if (field == 0)
				continue;

			abs_i = ABS(i);
			abs_j = ABS(j);
			// calc applying width
			applw = (width - abs_i);
			// calc applying height
			applh = (height - abs_j);

			pOutOffset = pBuffOut;
			pInOffset = pBuff;
			// if j < 0 then start source at beginning
			// if j < 0 then start dest at offset
			// if j > 0 then start source at offset
			// if j > 0 then start dest at beginning
			if (j < 0)
			{
				pOutOffset += (abs_j*stride);
			}
			if (j > 0)
			{
				pInOffset += (abs_j*stride);
			}
			// if i < 0 then start source at beginning;
			// if i < 0 then start dest at offset;
			// if i > 0 then start source at offset;
			// if i > 0 then start dest at beginning;
			if (i < 0)
			{
				pOutOffset += abs_i;
			}
			if (i > 0)
			{
				pInOffset += abs_i;
			}

			// Parse Buffer
			for (h = 0; h<applh; h++)
			{
				// Calc Starting Points
				pOut = pOutOffset + (h*stride);
				pIn = pInOffset + (h*stride);

				for (w = 0; w<applw; w++)
				{
					*pOut++ += (T_return(*pIn++) * field);
				}
			}
		}
	}
	// Apply Divisor and Offset
	if ((matrix->divisor != 1) || (matrix->offset != 0))
	{
		int divisor = matrix->divisor;
		int offset = matrix->offset;
		pOut = pBuffOut;
		size_t count = 0;
		for (count = 0; count<size; count++)
		{
			*pOut = T_return((double(*pOut) / divisor) + offset + 0.5);
			//*pOut = T_return((double(*pOut) / divisor) + offset);
			pOut++;
		}
	}
	return pBuffOut;
}

/*----------------------------------------*\
	template <typename T>
	T* convolute_T(T* pBuff, unsigned int width, unsigned int height, ConvolutionMatrix*  ConvMatrix)

	If pBuff is (unsigned char*) then 8 bit Channel
	If pBuff is (unsigned short*) then 16 bit Channel
	The side lengths of the matrices have to be unairy, e.g. 3x5, 3x3, 7x3, the matrix needs to have a center and of Type ConvolutionMatrix
	Applies a series or one convolution Matrix to the Buffer.
	Returns a new buffer (unsigned short*), must be deleted
\*----------------------------------------*/

template <typename T>
int* convolute_raw_T(T* pBuff, unsigned int width, unsigned int height, ConvolutionMatrix*  ConvMatrix)
{
	if (ConvMatrix->num_matrices() == 0)
		return 0;

	// Get First Matrix Buffer
	ConvolutionMatrix::ConvolutionMatrixData* matrix = ConvMatrix->get_matrix(0);

	int* pBuffOut = apply_convolution_matrix_T<T, int>(pBuff, width, height, matrix);

	// Apply Additional Matrices
	for (unsigned int i = 1; i < ConvMatrix->num_matrices(); i++)
	{
		matrix = ConvMatrix->get_matrix(i);
		int* pBuffOut2 = apply_convolution_matrix_T<int, int>(pBuffOut, width, height, matrix);
		delete pBuffOut;
		pBuffOut = pBuffOut2;
	}

	return pBuffOut;
}


template <typename T>
T* convolute_T(T* pBuff, unsigned int width, unsigned int height, ConvolutionMatrix*  ConvMatrix)
{
	int* pBuffOut = convolute_raw_T(pBuff, width, height, ConvMatrix);
	if (!pBuffOut) return 0;

	// Convert Back to unsigned T* Buffer
	int* pOut = pBuffOut;
	size_t size = width * height;
	T* pBuffChar = new T[size];
	T* pBuffCharRun = pBuffChar;
	T max = ~0;
	size_t count = 0;
	int _out = 0;

	for (count = 0; count<size; count++)
	{
		_out = *pOut++;
		if (_out < 0) *pBuffCharRun = 0;
		else if (_out > max) *pBuffCharRun = max;
		else *pBuffCharRun = (T)_out;
		pBuffCharRun++;
	}

	delete[] pBuffOut;
	return pBuffChar;
}


} // namespace ImageEffects

#endif // #ifndef __EFFECT_CONVOLUTIONMATRIX_H__
