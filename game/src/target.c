#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "image.h"
#include "target.h"
//Constructor
target newTarget(ALLEGRO_BITMAP *img) {
	target targetNew;
	targetNew.imagem = newImage(img);
	return targetNew;
}

void clearTarget(target this) {
	clearImage(this.imagem);
}

void drawTarget(target select) {
	draw(select.imagem);
}

void setPositionTarget(target select, int x, int y){
	setPositionx(select.imagem, x);
	setPositiony(select.imagem, y);
}

void drawTargets(target t1, target t2, target t3, target t4) {
	drawTarget(t1);
	drawTarget(t2);
	drawTarget(t3);
	drawTarget(t4);
}
