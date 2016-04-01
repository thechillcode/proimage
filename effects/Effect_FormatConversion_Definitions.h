/**********************************************************************************\
	Effect_FormatConversion.h
	
	Change Buffer between different Formats
\**********************************************************************************/

#ifndef __EFFECT_FORMATCONVERSION_DEF_H__
#define __EFFECT_FORMATCONVERSION_DEF_H__

namespace proimage
{

// MONO at [0,127] = 0; [128,255] = 1;
#define MONO(grey, threshold, max) ((threshold < grey) ? max : 0)
#define RGBTOGRAY(R,G,B) (double((unsigned int(30)*R) + (unsigned int(59)*G) + (unsigned int(11)*B))/100)

} // namespace proimage

#endif // #ifndef __EFFECT_FORMATCONVERSION_DEF_H__