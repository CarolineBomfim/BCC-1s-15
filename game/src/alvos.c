#include "include.h"
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
