#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "image.h"
#include "target.h"

#define FALSE 0
//Constructor
target newTarget(ALLEGRO_BITMAP *img) {
	target targetNew;
	targetNew.show = FALSE;
	targetNew.imagem = newImage(img);
	return targetNew;
}

void clearTarget(target this) {
	clearImage(this.imagem);
}

void drawTarget(target this) {
	if(this.show != FALSE) {
		draw(this.imagem);
	}
}

int getPositionTargetx(target this) {
	return getPositionx(this.imagem);
}

int getPositionTargety(target this) {
	return getPositiony(this.imagem);
}

void setPositionTargety(target this, int y) {
	setPositiony(this.imagem, y);
}

void setPositionTarget(target this, int x, int y){
	setPositionx(this.imagem, x);
	setPositiony(this.imagem, y);
}

void drawTargets(target t1, target t2, target t3, target t4) {
	drawTarget(t1);
	drawTarget(t2);
	drawTarget(t3);
	drawTarget(t4);
}
