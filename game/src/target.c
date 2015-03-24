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