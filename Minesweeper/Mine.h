#ifndef _MINE_H_
#define _MINE_H_

struct _MINE
{
	//mine or not
	bool is_mine; 
	//open or not
	bool is_open; 
	//surrounding mine numb
	char mine_num; 
};

typedef struct _MINE_GAME
{
	//width, height and mine numb
	int w, h, num; 
	//create the map
	_MINE* map; 
	//help function array
	int* help; 
}* MINEGAME;

MINEGAME createMINEGAME(int w, int h, int num);
//return -1 mentions failed
//return 0 mentions normal
//return 1 mentions success
int playMINEGAME(MINEGAME mg, int x, int y);
void endMINEGAME(MINEGAME mg);

#endif
