/**========================================================================================================================**\
	Algorithm_GaussFunction.h

	Simple functions to a 1D Gauss curve for computation
\**========================================================================================================================**/

#ifndef __CALC_GAUSS_KERNEL__
#define __CALC_GAUSS_KERNEL__

namespace imgeffects
{

/*--------------------------------------------------------------------------------*\
	double gauss_get_sigma_from_radius(int radius, double* sigma)

	returns the standard sigma to the given radius, function width is (radius*2)+1
\*--------------------------------------------------------------------------------*/
double gauss_get_sigma_from_radius(int radius);

/*--------------------------------------------------------------------------------*\
	int* gauss_get_kernel(double sigma, int width, int* sum);

	Returns a new 1D gauss kernel for supplied sigma and width (width has to be unairy)
	The smallest element (most left, most right) is usually one
	The number of elements returned is width
	sum is the number of all elements calculated together
\*--------------------------------------------------------------------------------*/
int* gauss_get_kernel(double sigma, int width, int* sum);

/*--------------------------------------------------------------------------------*\
	int* gaussfunc_get_kernel(double sigma, int width, int* sum);

	Returns a new 1D gauss kernel for supplied sigma and width (width has to be unairy)
	The smallest element (most left, most right) is usually one
	The number of elements returned is width
	sum is the number of all elements calculated together
\*--------------------------------------------------------------------------------*/
double* gauss_get_kernel(double sigma, int width, double* sum);

} // namespace imgeffects

#endif // #ifndef __CALC_GAUSS_KERNEL__