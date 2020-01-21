#define _QP_W 8
#define _QP_H 8
#define _QP_S (_QP_W * _QP_H)
#define _KZ 0
#define _HZ 1
#define _BZ 2

extern char qp[_QP_S];
extern char c;

//initilize
void HBQ_Init();

//if x and y parameter wrong, return -2
//cannot setting chess return -1
//setting chess but no one win return 0
//setting chess, someone win return 1
int HBQ_Play(int x, int y);