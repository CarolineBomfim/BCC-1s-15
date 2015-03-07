#include "include.h"
#define TRUE  1
#define FALSE 0
//Constructor
barstatus newBar(int allcapacity, int starting, int position, ALLEGRO_BITMAP *barimage) {
	barstatus newbarstatus;
	newbarstatus.total = allcapacity;
	newbarstatus.atual = malloc(sizeof(int));
	newbarstatus.imagem = newImage(barimage);
	setBar(newbarstatus, starting);
	setPositiony(newbarstatus.imagem, position);
	setPositionx(newbarstatus.imagem, starting);
	return newbarstatus;
}

void clearBar(barstatus this){
	clearImage(this.imagem);
}

void drawStatusBar(barstatus bar) {
	int status = 0;
	int aux = 0;
	while(status < bar.atual[0]) {
		setPositionx(bar.imagem, aux);
		draw(bar.imagem);
		status++;
		aux += bar.imagem.width;
	}
}

void reduceBar(barstatus bar, int reduced) {
	bar.atual[0] -= reduced;
}

void updateBar(barstatus bar, int up) {
	bar.atual[0] += up;
}
void setBar(barstatus this, int x) {
	this.atual[0] = x;
}
int getBar(barstatus this) {
	return this.atual[0];
}
void setBarPosition(barstatus it, int x, int y) {
	setPositionx(it.imagem, x);
	setPositiony(it.imagem, y);
}
