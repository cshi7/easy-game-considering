#include <iostream>
#include <conio.h>
#include "ConsoleRender.h"
#include "Mine.h"

#define _GAME_W 20
#define _GAME_H 20
#define _GAME_N 10

void main()
{
	const char* s1[] = {"£±","£²","£³","£´","£µ","£¶","£·","£¸"};
	const char* s2[] = {"¢Ù","¢Ú","¢Û","¢Ü","¢Ý","¢Þ","¢ß","¢à"};

	MINEGAME mg = createMINEGAME(_GAME_W, _GAME_H, _GAME_N);
	CR cr = createCR(_GAME_W, _GAME_H);
	int x = 0, y = 0;
	
	while (1)
	{
		system("cls");
		clearCR(cr);
		for (int i = 0; i < _GAME_W * _GAME_H; ++i)
		{
			//try to get the x,y coordinates
			int cx = i % _GAME_W, cy = i / _GAME_W;

			//to check where is the mouse
			if (x == cx && y == cy)
			{
				if (mg->map[i].is_open)
				{
					if (mg->map[i].mine_num > 0)
						setCR(cr, cx, cy, s2[mg->map[i].mine_num - 1]);
					else
						setCR(cr, cx, cy, "¡ð");
				}
				else
					setCR(cr, cx, cy, "¡õ");
			}
			//if there is no mouse
			else
			{
				if (mg->map[i].is_open)
				{
					if (mg->map[i].mine_num > 0)
						setCR(cr, cx, cy, s1[mg->map[i].mine_num - 1]);
				}
				else
					setCR(cr, cx, cy, "¡ö");
			}
		}
		renderCR(cr);

		int input = _getch();
		if ((input == 'w' || input == 'W') && y > 0)
			--y;
		if ((input == 's' || input == 'S') && y < _GAME_H - 1)
			++y;
		if ((input == 'a' || input == 'A') && x > 0)
			--x;
		if ((input == 'd' || input == 'D') && x < _GAME_W - 1)
			++x;
		if (input == ' ')
		{
			int r = playMINEGAME(mg, x, y);
			if (r == -1)
			{
				std::cout<<"You Failed,";
				break;
			}
			else if (r == 1)
			{
				std::cout<<"You Win,";
				break;
			}
		}
	}

	destroyCR(cr);
	endMINEGAME(mg);

	system("pause");
}