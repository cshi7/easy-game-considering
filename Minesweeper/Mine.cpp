#include "Mine.h"
#include <iostream>
#include <time.h>

MINEGAME createMINEGAME(int w, int h, int num)
{
	if (w < 1 || h < 1 || num < 1)
		return 0;

	srand((unsigned int)time(0));

	MINEGAME mg =  (MINEGAME)malloc(sizeof(_MINE_GAME));
	mg->w = w;
	mg->h = h;
	mg->num = num;
	mg->map = (_MINE*)malloc(sizeof(_MINE) * mg->w * mg->h);
	mg->help = (int*)malloc(sizeof(int) * mg->w * mg->h);

	//we want to initialize the map
	//try to close all the blocks in the map, and set it to no mine
	int s = mg->w * mg->h;
	for (int i = 0; i < s; ++i)
	{
		mg->map[i].is_mine = false;
		mg->map[i].is_open = false;
	}

	//now setting the mine
	int* p = (int*)malloc(sizeof(int) * s);
	for (int i = 0; i < s; ++i)
		p[i] = i;
	for (int i = 0; i < num; ++i)
	{
		int index = rand() % s; //10
		mg->map[p[index]].is_mine = true;
		p[index] = p[s - 1];
		s -= 1;
	}
	free(p);

	//calculate the surrounding mine numb
	s = mg->w * mg->h;
	//701
	//6 2
	//543
	int xd[] = {0,1,1,1,0,-1,-1,-1};
	int yd[] = {-1,-1,0,1,1,1,0,-1};
	for (int i = 0; i < s; ++i)
	{
		mg->map[i].mine_num = 0;
		int x = i % mg->w, y = i / mg->w;
		for (int j = 0; j < 8; ++j)
		{
			int cx = x + xd[j], cy = y + yd[j];
			if (cx >= 0 && cx < mg->w && cy >= 0 && cy < mg->h)
			{
				if (mg->map[cx + cy * mg->w].is_mine)
					mg->map[i].mine_num += 1;
			}
		}
	}

	return mg;
}

int playMINEGAME(MINEGAME mg, int x, int y)
{
	if (mg->map[x + y * mg->w].is_mine)
		return -1;

	//click to open a block
	mg->help[0] = x + y * mg->w;
	//valid length
	int help_len = 1; 

	//for loops
	int begin = 0, end = 0;

	//open blocks loop
	int xd[] = {0,1,1,1,0,-1,-1,-1};
	int yd[] = {-1,-1,0,1,1,1,0,-1};
	while (1)
	{
		int cur_help_len = help_len;

		for (int i = begin; i <= end; ++i)
		{
			//open the block if the surrouding mine numb is 0
			if (mg->map[mg->help[i]].mine_num == 0)
			{
				int x = mg->help[i] % mg->w;
				int y = mg->help[i] / mg->w;

				//check the eight direction of the block
				for (int j = 0; j < 8; ++j)
				{
					int cx = x + xd[j], cy = y + yd[j];
					if (cx >= 0 && cx < mg->w && cy >= 0 && cy < mg->h)
					{
						//if it is not mine
						if (!mg->map[cx + cy * mg->w].is_mine)
						{
							//check the help functions work correct
							bool no = true;
							for (int k = 0; k < help_len; ++k)
							{
								if (mg->help[k] == cx + cy * mg->w)
								{
									no = false;
									break;
								}
							}
							if (no)
								mg->help[help_len++] = cx + cy * mg->w;
						}
					}
				}
			}
		}

		if (cur_help_len == help_len)
			break;
		else
		{
			begin = cur_help_len;
			end = help_len - 1;
		}
	}
	for (int i = 0; i < help_len; ++i)
		mg->map[mg->help[i]].is_open = true;

	//check if success or not
	for (int i = 0; i < mg->w * mg->h; ++i)
	{
		if (!mg->map[i].is_mine && !mg->map[i].is_open)
			return 0;
	}

	return 1;
}

void endMINEGAME(MINEGAME mg)
{
	free(mg->help);
	free(mg->map);
	free(mg);
}