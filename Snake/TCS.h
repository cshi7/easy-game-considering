#define _MAP_MIN_W 5
#define _MAP_MAX_W 20
#define _MAP_MIN_H 5
#define _MAP_MAX_H 20

#define _INPUT_NONE 0
#define _INPUT_UP 1
#define _INPUT_DOWN 2
#define _INPUT_LEFT 3
#define _INPUT_RIGHT 4

#define _KD 0
#define _ZA 1
#define _ST 2
#define _SS 3
#define _GZ 4

bool Init(int w, int h);

int Run(int input);

const char* Map();