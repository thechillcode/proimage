
#ifndef __CONSTRAINNUMBER_H__
#define __CONSTRAINNUMBER_H__

template <class TNum, class TBoarder>
inline TNum constrain(TNum num, TBoarder min, TBoarder max)
{
	if (num < min) return min;
	if (num > max) return max;
	return TBoarder(num);
}

#endif // #ifndef __CONSTRAINNUMBER_H__