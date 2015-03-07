#ifndef _TARGET_H_
#define _TARGET_H_
#include "images.h"

typedef struct _target {
	image imagem;
}target;
//Constructor

target newTarget(ALLEGRO_BITMAP *img);

void drawTarget(target select);

void setPositionTarget(target select, int x, int y);

void clearTarget(target this);

#endif
