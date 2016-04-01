/**********************************************************************************\
	Effect_Rotation.h
	
	Rotate an image
	If angle is positive then image is rotated clockwize
	If angle is negative then image is rotated counter clokcwize
	This due to the image height is positive
\**********************************************************************************/

#ifndef __TRANSFORM_ROTATION__
#define __TRANSFORM_ROTATION__

namespace proimage
{

/*----------------------------------------*\
	unsigned char* Rotate_degre_Gray8(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, float angle, unsigned int* new_width, unsigned int* new_height);

	bpp := Bits Per Pixel
	Rotate an image by given angle, angle is counter clock wize
	Return a new buffer, has be deleted using delete []
\*----------------------------------------*/
unsigned char* rotate(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, float angle, double rot_x, double rot_y, unsigned int* new_width, unsigned int* new_height);
unsigned char* rotate_rad(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp, float rad, double rot_x, double rot_y, unsigned int* new_width, unsigned int* new_height);

/*----------------------------------------*\
	unsigned char* Rotate_90_Ch8(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp);

	bpp := Bits Per Pixel
	Rotate an image by 90 degress clock wize
	width and height are swaped.
	Return a new buffer, has be deleted using delete []
\*----------------------------------------*/
unsigned char* rotate_90(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp);

/*----------------------------------------*\
	unsigned char* Rotate_180_Ch8(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp);
	
	bpp := Bits Per Pixel
	Rotate an image by 180 degress clock wize
	Return a new buffer, has be deleted using delete []
\*----------------------------------------*/
unsigned char* rotate_180(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp);

/*----------------------------------------*\
	unsigned char* Rotate_270_Ch8(unsigned char* pBuff, unsigned int width, unsigned int height, unsigned int bpp);

	bpp := Bits Per Pixel
	Rotate an image by 270 degress clock wize
	width and height are swaped.
	Return a new buffer, has be deleted using delete []
\*----------------------------------------*/
unsigned char* rotate_270(unsigned char* pBuff, unsigned int width, unsigned int height,unsigned int bpp);

} // namespace ImageEffects

#endif // #ifndef __TRANSFORM_ROTATION__