#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "global.h"
#include "image.h"
#include "target.h"

//Constructor
target newTarget(ALLEGRO_BITMAP *img) {
	target targetNew;
	int *tmp = malloc(sizeof(int));
	tmp[0] = FALSE;
	targetNew.show = tmp;
	targetNew.imagem = newImage(img);
	return targetNew;
}

void clearTarget(target this) {
	clearImage(this.imagem);
}

void drawTarget(target this) {
	if(this.show[0] != FALSE) {
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

bool isShow(target this) {
	return this.show[0];
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

void cascateTargets(global_var *global, target t1, target t2, target t3, target t4) {
	if(isShow(t1))
		setPositionTargety(t1, getPositionTargety(t1) + global->configure->cascateSpeed);
	if(isShow(t2))
		setPositionTargety(t2, getPositionTargety(t2) + global->configure->cascateSpeed);
	if(isShow(t3))
		setPositionTargety(t3, getPositionTargety(t3) + global->configure->cascateSpeed);
	if(isShow(t4))
		setPositionTargety(t4, getPositionTargety(t4) + global->configure->cascateSpeed);
}

void showTarget(target this) {
	if(!this.show[0])
		this.show[0] = TRUE;
}

void hideTarget(target this) {
	if(this.show[0])
		this.show[0] = FALSE;
}
