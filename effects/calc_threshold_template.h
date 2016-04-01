/**********************************************************************************\
	Algorithm_Threshold_Otzu_Template.h
	
	Alogrithm Otzu, to detect Gray Threshold
\**********************************************************************************/

#ifndef __ALGO_THRESHOLD_OTZU_TEMPLATE_H__
#define __ALGO_THRESHOLD_OTZU_TEMPLATE_H__

#include <memory>

namespace proimage
{

/*----------------------------------------*\
	Function()

	Get a suggested threshold via Otzu Algo
	http://de.wikipedia.org/wiki/Schwellwertverfahren
	http://www.gomatlab.de/otsu-verfahren-bitte-um-hilfe-t16276.html
	
	Calc Otzu for multiple of 8 bit grayscale buffers
\*----------------------------------------*/
template <class T>
T calc_threshold_otzu_T_OLD(T* buffer, unsigned int width, unsigned int height)
{
	T* _buffer = 0;
	T max_values = (~0);
	unsigned long long* histogram = new unsigned long long[max_values];
	memset(histogram, 0, sizeof(unsigned long long)*max_values);
	unsigned long long size = width*height;
	unsigned int i = 0;
	unsigned int row = 0;
	unsigned int col = 0;
	unsigned int _val = 0;

	// Get Histogram
	// Get all grey values
	_buffer = buffer;
	unsigned long long _fullgrey = 0;
	for (row = 0; row < height; row++)
	{
		for (col = 0; col < width; col++)
		{	
			_val = *_buffer++;
			_fullgrey += _val;
			histogram[_val] += 1;
		}
	}

	// Average Gray Value
	unsigned long long m_grey = unsigned long long(_fullgrey/size);

	// Probability of Gray Value [0,1]
	float* pGrayValue = new float[max_values];
	memset(pGrayValue, 0, sizeof(float)*max_values);
	for (i=0; i<max_values; i++)
	{
		pGrayValue[i] = (float)histogram[i]/size;
	}

	float _q = 0;
	T _thres = 0;
	unsigned long long m_C1 = 0;
	unsigned long long sum_C1 = 0;
	float p_C1 = 0;
	unsigned long long m_C2 = 0;
	unsigned long long sum_C2 = 0;
	float p_C2 = 0;
	float s_C1 = 0;
	float s_C2 = 0;
	float s_bet = 0;
	float s_in = 0;
	float q = 0;

	// 0 - 255; C1; C2
	// Iterate through all thresholds and check for the best one
	for (T thres = 0; thres < max_values; thres++)
	{
		// average grey values of C1
		// average grey of values C2
		m_C1 = 0;
		sum_C1=0;
		m_C2 = 0;
		sum_C2=0;
		_buffer = buffer;
		for (row = 0; row < height; row++)
		{
			for (col = 0; col < width; col++)
			{	
				_val = *_buffer++;
				if (_val > thres)
				{
					m_C2 += _val;
					sum_C2++;
				}
				else
				{
					m_C1 += _val;
					sum_C1++;
				}
			}
		}
		if (sum_C1 > 0)
			m_C1 = unsigned long long(m_C1/sum_C1);
		if (sum_C2 > 0)
			m_C2 = unsigned long long(m_C2/sum_C2);

		// probability of all values in C1
		p_C1 = 0;
		for (i=0; i<thres; i++)
			p_C1 += pGrayValue[i];
	
		// probability of all values in C2
		p_C2 = 1-p_C1;

		// Spread C1
		s_C1 = 0;
		for (i=0; i<thres; i++)
		{
			s_C1 += ((i-m_C1)*(i-m_C1)) * pGrayValue[i];
		}
		// Spread C2
		s_C2 = 0;
		for (i=thres; i<256; i++)
		{
			s_C2 += ((i-m_C2)*(i-m_C2)) * pGrayValue[i];
		}

		// Spread inbetween
		s_bet = (p_C1* ((m_C1-m_grey)*(m_C1-m_grey))) + (p_C2 * ((m_C2-m_grey)*(m_C2-m_grey)));
		s_in = (p_C1*s_C1) + (p_C2*s_C2);

		// Quotient
		q = s_bet / s_in;
		if (q > _q)
		{
			_q = q;
			_thres = thres;
		}
	}
	delete [] histogram;
	delete [] pGrayValue;
	return _thres;
}

/*----------------------------------------*\
Function()

Get a suggested threshold via Otzu Algo
http://de.wikipedia.org/wiki/Schwellwertverfahren
http://www.gomatlab.de/otsu-verfahren-bitte-um-hilfe-t16276.html

Calc Otzu for multiple of 8 bit grayscale buffers
\*----------------------------------------*/
template <class T>
T calc_threshold_otzu_T(T* buffer, unsigned int width, unsigned int height)
{
	T* _buffer = 0;
	T max_values = (~0);
	size_t* histogram = new size_t[max_values];
	memset(histogram, 0, sizeof(size_t)*max_values);
	size_t size = width*height;
	size_t i = 0;
	size_t row = 0;
	size_t col = 0;
	size_t _val = 0;

	// Get Histogram
	// Get all grey values
	_buffer = buffer;
	size_t _fullgrey = 0;
	for (row = 0; row < height; row++)
	{
		for (col = 0; col < width; col++)
		{
			_val = *_buffer++;
			_fullgrey += _val;
			histogram[_val] += 1;
		}
	}

	// Average Gray Value
	size_t m_grey = size_t(_fullgrey / size);

	// Probability of Gray Value [0,1]
	double* pGrayValue = new double[max_values];
	memset(pGrayValue, 0, sizeof(double)*max_values);
	for (i = 0; i < max_values; i++)
	{
		pGrayValue[i] = (double)histogram[i] / size;
	}

	double _q = 0;
	T _thres = 0;
	size_t m_C1 = 0;
	size_t sum_C1 = 0;
	double p_C1 = 0;
	size_t m_C2 = 0;
	size_t sum_C2 = 0;
	double p_C2 = 0;
	double s_C1 = 0;
	double s_C2 = 0;
	double s_bet = 0;
	double s_in = 0;
	double q = 0;

	// 0 - 255; C1; C2
	// Iterate through all thresholds and check for the best one
	for (T thres = 0; thres < max_values; thres++)
	{
		// average grey values of C1
		// average grey of values C2
		m_C1 = 0;
		sum_C1 = 0;
		m_C2 = 0;
		sum_C2 = 0;
		_buffer = buffer;
		for (row = 0; row < height; row++)
		{
			for (col = 0; col < width; col++)
			{
				_val = *_buffer++;
				if (_val > thres)
				{
					m_C2 += _val;
					sum_C2++;
				}
				else
				{
					m_C1 += _val;
					sum_C1++;
				}
			}
		}
		if (sum_C1 > 0)
			m_C1 = size_t(m_C1 / sum_C1);
		if (sum_C2 > 0)
			m_C2 = size_t(m_C2 / sum_C2);

		// probability of all values in C1
		p_C1 = 0;
		for (i = 0; i < thres; i++)
			p_C1 += pGrayValue[i];

		// probability of all values in C2
		p_C2 = 1 - p_C1;

		// Spread C1
		s_C1 = 0;
		for (i = 0; i < thres; i++)
		{
			s_C1 += ((i - m_C1)*(i - m_C1)) * pGrayValue[i];
		}
		// Spread C2
		s_C2 = 0;
		for (i = thres; i < 256; i++)
		{
			s_C2 += ((i - m_C2)*(i - m_C2)) * pGrayValue[i];
		}

		// Spread inbetween
		s_bet = (p_C1* ((m_C1 - m_grey)*(m_C1 - m_grey))) + (p_C2 * ((m_C2 - m_grey)*(m_C2 - m_grey)));
		s_in = (p_C1*s_C1) + (p_C2*s_C2);

		// Quotient
		q = s_bet / s_in;
		if (q > _q)
		{
			_q = q;
			_thres = thres;
		}
	}
	delete[] histogram;
	delete[] pGrayValue;
	return _thres;
}

} // namespace ImageEffects


#endif // #ifndef __ALGO_THRESHOLD_OTZU_TEMPLATE_H__