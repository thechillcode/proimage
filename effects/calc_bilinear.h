/**========================================================================================================================**\
	calc_bilinear.h

	next ### Interpolation Bicubic ###
\**========================================================================================================================**/

#ifndef __CALC_BILINEAR__
#define __CALC_BILINEAR__

namespace imgeffects
{

	/*--------------------------------------------------------------------------------*\
		T get_pixel (T* pBuff, unsigned int width, unsigned int height, int i, int j)

		Returns the Value of a given coordinates, returns 0 if coordinates are not in image
		\*--------------------------------------------------------------------------------*/

	template <typename T>
	__forceinline T get_pixel(T* pBuff, unsigned int width, unsigned int height, int i, int j)
	{
		if ((i < 0) || (i > int(width - 1))) return 0;
		if ((j < 0) || (j > int(height - 1))) return 0;
		return *(pBuff + (width*j) + i);
	}

	/*--------------------------------------------------------------------------------*\
		T calc_bilinear_value (T* pBuff, unsigned int width, unsigned int height, double dx, double dy)

		Returns the Blinear Value of a given Pixel coordinate
		\*--------------------------------------------------------------------------------*/
	template <typename T>
	__forceinline T calc_bilinear_value(T* pBuff, unsigned int width, unsigned int height, double dx, double dy)
	{
		// Only calc if [-1,-1] [width,height]
		if (!((dx > -1) && (dx < width) && (dy > -1) && (dy < height)))
			return 0;

		// get fractional parts
		double _intpart_x = 0;
		double _intpart_y = 0;
		double _dx = modf(dx, &_intpart_x);
		double _dy = modf(dy, &_intpart_y);
		int x = int(_intpart_x);
		int y = int(_intpart_y);

		if ((_dx == 0) && (_dy == 0))
		{
			return get_pixel(pBuff, width, height, unsigned int(dx), unsigned int(dy));
		}

		double x1, x2, val;
		T p1, p2, p3, p4;

		p1 = get_pixel(pBuff, width, height, x, y);
		p2 = get_pixel(pBuff, width, height, x, y + 1);
		p3 = get_pixel(pBuff, width, height, x + 1, y + 1);
		p4 = get_pixel(pBuff, width, height, x + 1, y);

		x1 = (_dx*(p4 - p1)) + p1;
		x2 = (_dx*(p3 - p2)) + p2;
		val = (_dy*(x2 - x1)) + x1;
		// round output value
		return (T)(val + 0.5);
	}

} // namespace imgeffects


#endif // #ifndef __CALC_BILINEAR__