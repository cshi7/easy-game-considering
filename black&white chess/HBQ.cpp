#include "HBQ.h"

#define _ZX(x,y) ((x)+(y)*_QP_W)
#define _XZ_X(i) ((i)%_QP_W)
#define _XZ_Y(i) ((i)/_QP_W)
#define _IN_QP(x,y) ((x)>=0&&(x)<_QP_W&&(y)>=0&&(y)<_QP_H)

char qp[_QP_S];
char c;

//return true mentions can put chess here
//return false mentions cannot put chess here
//change when true for setting new chess
//if change true, change the middle chess color
//if change false, do not change middle chess color
bool HBQ_LuoZi(int x, int y, bool change)
{
	//the array that mentions eight direction can set chess or not 
	//bool b[8] = {};
	char lz = 0;

	//701
	//6 2
	//543
	const int xbh[] = {0,1,1,1,0,-1,-1,-1};
	const int ybh[] = {-1,-1,0,1,1,1,0,-1};

	//loop for eight direction
	for (int i = 0; i < 8; ++i)
	{
		bool zd = false;
		int x2 = x + xbh[i] * 2, y2 = y + ybh[i] * 2;
		for (; _IN_QP(x2, y2); x2 += xbh[i], y2 += ybh[i])
		{
			if (qp[_ZX(x2, y2)] == c)
			{
				zd = true;
				break;
			}
		}
		if (zd)
		{
			//enemy color
			char cc = (c == _HZ ? _BZ : _HZ);

			//change the chess color
			bool bs = true;

			//loop justify
			x2 -= xbh[i];
			y2 -= ybh[i];
			int x3 = x2, y3 = y2;
			for (; x2 != x || y2 != y; x2 -= xbh[i], y2 -= ybh[i])
			{
				if (qp[_ZX(x2, y2)] != cc)
				{
					bs = false;
					break;
				}
			}

			if (bs)
			{
				//setting this direction flag to true
				//b[i] = true;
				lz |= (1 << i);

				//if change true, change color
				if (change)
				{
					for (; x3 != x || y3 != y; x3 -= xbh[i], y3 -= ybh[i])
						qp[_ZX(x3, y3)] = c;
				}
			}
		}
	}

	//for (int i = 0; i < 8; ++i)
	//{
	//	if (b[i])
	//		return true;
	//}
	//return false;

	//return *((double*)b) != 0.0;

	if (lz && change)
	{
		qp[_ZX(x, y)] = c;
		c = (c == _HZ ? _BZ : _HZ);
	}

	return lz != 0;
}

void HBQ_Init()
{
	//initilize
	for (int i = 0; i < _QP_S; ++i)
		qp[i] = _KZ;
	qp[_ZX(3, 3)] = qp[_ZX(4, 4)] = _HZ;
	qp[_ZX(3, 4)] = qp[_ZX(4, 3)] = _BZ;

	c = _HZ;
}

int HBQ_Play(int x, int y)
{
	//parameter checking
	if (!_IN_QP(x, y))
		return -2;

	//chess setting check
	if (!HBQ_LuoZi(x, y, false))
		return -1;
	else
		HBQ_LuoZi(x, y, true);

	//win or not
	int hzn = 0, bzn = 0;
	for (int i = 0; i < _QP_S; ++i)
	{
		if (qp[i] == _KZ)
			return 0;
	}

	//if someone win
	return 1;
}