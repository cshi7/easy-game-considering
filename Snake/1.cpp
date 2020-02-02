#include <iostream>
#include <windows.h>
#include "TCS.h"

void main()
{
	//symbols
	const char* s[] = {"¡õ", "¡ö", "¡ô", "¡ñ", "¡ï"};

	int w, h;
	std::cin>>w>>h;

	if (Init(w, h))
	{
		while (1)
		{
			system("cls");
			const char* p = Map();
			for (int i = 0; i < w * h; ++i)
			{
				std::cout<<s[p[i]];
				if (i % w == w - 1)
					std::cout<<std::endl;
			}

			int input = _INPUT_NONE;
			if (GetAsyncKeyState(VK_UP) & 1)
				input = _INPUT_UP;
			if (GetAsyncKeyState(VK_DOWN) & 1)
				input = _INPUT_DOWN;
			if (GetAsyncKeyState(VK_LEFT) & 1)
				input = _INPUT_LEFT;
			if (GetAsyncKeyState(VK_RIGHT) & 1)
				input = _INPUT_RIGHT;
			int r = Run(input);
			if (r <= 0)
				break;

			Sleep(100);
		}
	}
	else
		std::cout<<"Initialize failed, Please try again!";

	system("pause");
}