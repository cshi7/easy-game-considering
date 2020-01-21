#include <iostream>
#include <conio.h>
#include "HBQ.h"

void main()
{
	int x = 0, y = 0;
	HBQ_Init();

	while (1)
	{
		system("cls");
		for (int i = 0; i < _QP_S; ++i)
		{
			if (x + y * _QP_W == i)
			{
				switch (qp[i])
				{
				case _KZ: std::cout<<"��"; break;
				case _HZ: std::cout<<"��"; break;
				case _BZ: std::cout<<"��"; break;
				}
			}
			else
			{
				switch (qp[i])
				{
				case _KZ: std::cout<<"��"; break;
				case _HZ: std::cout<<"��"; break;
				case _BZ: std::cout<<"��"; break;
				}
			}
			if (i % _QP_W == _QP_W - 1)
				std::cout<<std::endl;
		}
		std::cout<<"currently["<<(c == _HZ ? "��" : "��")<<"]";

		int input = _getch();
		if (input == 'w' && y > 0)
			--y;
		if (input == 's' && y < _QP_H - 1)
			++y;
		if (input == 'a' && x > 0)
			--x;
		if (input == 'd' && x < _QP_W - 1)
			++x;
		if (input == ' ')
		{
			int r = HBQ_Play(x, y);
			if (r == 1)
			{
				std::cout<<(c == _HZ ? "black" : "white")<<"chess win!";
				break;
			}
			else if (r == -1)
			{
				std::cout<<"cannot put here,";
				system("pause");
			}
		}
	}

	system("pause");
}