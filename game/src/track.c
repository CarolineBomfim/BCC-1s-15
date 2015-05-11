#include <stdlib.h>
#include "global.h"

int **track(global_var *global) {
	int r[2][2];
	r[0][0] = 0;
	r[0][1] = 0;
	r[1][0] = 0;
	r[1][1] = 0;
	return r;
}