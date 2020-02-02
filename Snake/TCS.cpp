#include "TCS.h"
#include <iostream>
#include <time.h>

bool init = false;
char map[_MAP_MAX_W * _MAP_MAX_H];
int w, h;
int she[_MAP_MAX_W * _MAP_MAX_H], she_num = 0, she_dir = 0; //the snake
int zhangai[_MAP_MAX_W * _MAP_MAX_H], zhangai_num = 0; //barrier
int gz; //fruit

bool Init(int w, int h)
{
	srand((unsigned int)time(0));

	if (w < _MAP_MIN_W || w > _MAP_MAX_W || h < _MAP_MIN_H || h > _MAP_MAX_H)
		return init = false;
	else
	{
		::w = w;
		::h = h;

		//initialize snake
		she[0] = rand() % (::w * ::h);
		she_num = 1;
		//here we want to use 0,1,2,3 to show the direction
		//where 0 for up, 1 for down, 2 for left and 3 for right
		she_dir = rand() % 4; 

		//initialize barrier
		zhangai_num = (::w * ::h) / 40;
		for (int i = 0; i < zhangai_num; ++i)
			zhangai[i] = rand() % (::w * ::h);

		//initialize fruit
		gz = rand() % (::w * ::h);

		return init = true;
	}
}

int Run(int input)
{
	if (!init)
		return -3;
	if (input < _INPUT_NONE || input > _INPUT_RIGHT)
		return -2;

	if (input != 0)
	{
		switch (she_dir)
		{
			//if the direction right now is up-down, and want to go to left-right
			case 0:
			case 1:
			{
				if (input == _INPUT_LEFT || input == _INPUT_RIGHT)
					she_dir = input - 1;
				break;
			}
			//if the direction right now is left-right, and want to go to up-down
			case 2:
			case 3:
			{
				if (input == _INPUT_UP || input == _INPUT_DOWN)
					she_dir = input - 1;
				break;
			}
		}
	}

	//if snake head hit the fruit
	bool df = false;
	if (she[0] == gz)
	{
		gz = rand() % (w * h);
		she_num += 1;
		df = true;
	}

	//if snake head hit itself
	for (int i = 1; i < she_num; ++i)
	{
		if (she[0] == she[i])
			return 0;
	}

	//if snake head hit the barrier
	for (int i = 0; i < zhangai_num; ++i)
	{
		if (she[0] == zhangai[i])
			return -1;
	}

	//setting the movement of snake body
	for (int i = she_num - 1; i > 0; --i)
		she[i] = she[i -  1];

	//the movement of snake head
	int x = she[0] % w, y = she[0] / w;
	switch (she_dir)
	{
	case 0:
		{
			y = (y == 0 ? h - 1 : y - 1);
			break;
		}
	case 1:
		{
			y = (y == h - 1 ? 0 : y + 1);
			break;
		}
	case 2:
		{
			x = (x == 0 ? w - 1 : x - 1);
			break;
		}
	case 3:
		{
			x = (x == w - 1 ? 0 : x + 1);
			break;
		}
	}
	she[0] = x + y * w;

	return df ? 2 : 1;
}

const char* Map()
{
	if (!init)
		return 0;

	for (int i = w * h; i >= 0; --i)
		map[i] = _KD;
	for (int i = 0; i < zhangai_num; ++i)
		map[zhangai[i]] = _ZA;
	map[she[0]] = _ST;
	for (int i = 1; i < she_num; ++i)
		map[she[i]] = _SS;
	map[gz] = _GZ;
	return map;
}