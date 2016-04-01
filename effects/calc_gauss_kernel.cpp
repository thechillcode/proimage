/**========================================================================================================================**\
	Algorithm_GaussFunction.cpp

	Simple functions to a 1D Gauss curve for computation
\**========================================================================================================================**/

#include "calc_gauss_kernel.h"
#define _USE_MATH_DEFINES
#include <cmath>

namespace proimage
{

double gauss_get_sigma_from_radius(int radius)
{
	// width = (radius*2)+1;
	return double(radius)/3;
}

int* gauss_get_kernel(double sigma, int width, int* sum)
{
	int i=0;
	double sig_sig_2 = sigma*sigma*2;

	int k_1 = (width-1)/2;

	int _num = 0;
	int _sum = 0;
	int* iG_1D = new int[width];
	iG_1D[0] = 1;
	iG_1D[width-1] = 1;
	int k1k1 = k_1*k_1;
	_sum = (int)floor(pow(M_E, double(k1k1)/sig_sig_2)+0.5);
	iG_1D[k_1] = _sum;
	for (i=1; i<k_1; i++)
	{
		_num = (int)floor(pow(M_E, double(k1k1-(i*i))/sig_sig_2)+0.5);
		iG_1D[k_1+i] = _num;
		iG_1D[k_1-i] = _num;
		_sum += (_num*2);
	}
	_sum += 2;
	*sum = _sum;
	return iG_1D;
}

double* gauss_get_kernel(double sigma, int width, double* sum)
{
	int i=0;
	double sig_sig_2 = sigma*sigma*2;

	int k_1 = (width-1)/2;

	double _num = 0;
	double _sum = 0;
	double* iG_1D = new double[width];
	iG_1D[0] = 1;
	iG_1D[width-1] = 1;
	int k1k1 = k_1*k_1;
	_sum = pow(M_E, double(k1k1)/sig_sig_2);
	iG_1D[k_1] = _sum;
	for (i=1; i<k_1; i++)
	{
		_num = pow(M_E, double(k1k1-(i*i))/sig_sig_2);
		iG_1D[k_1+i] = _num;
		iG_1D[k_1-i] = _num;
		_sum += (_num*2);
	}
	_sum += 2;
	*sum = _sum;
	return iG_1D;
}

} // namespace proimage