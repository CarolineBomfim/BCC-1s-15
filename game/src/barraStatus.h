#ifndef _STATUS_BAR_H_
#define _STATUS_BAR_H_
#include "images.h"

typedef struct _barstatus {
	int total;
	int *atual;
	int positiony;
	image imagem;
}barstatus;

//Constructor
barstatus newBar(int allcapacity, int starting, int position, ALLEGRO_BITMAP *barimage);

void clearBar(barstatus this);

void drawStatusBar(barstatus bar);
void setBar(barstatus this, int x);
int getBar(barstatus this);
void reduceBar(barstatus bar, int reduced);

void updateBar(barstatus bar, int up);

void setBarPosition(barstatus it, int x, int y);

#endif
