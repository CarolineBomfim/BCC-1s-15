#include "include.h"

int getWidth(ALLEGRO_BITMAP *img){
	return al_get_bitmap_width(img);
}

int getHeight(ALLEGRO_BITMAP *img) {
	return al_get_bitmap_height(img);
}

void setPositionx(image img, int newPosition) {
	img.positionx[0] = newPosition;
}

void setPositiony(image img, int newPosition) {
	img.positiony[0] = newPosition;
}

int getPositionx(image img) {
	return img.positionx[0];
}

int getPositiony(image img) {
	return img.positiony[0];
}

int getImageHeight(image img) {
	return img.height;
}

int getImageWidth(image img) {
	return img.width;
}

void draw(image img) {
	int x = 0, y = 0;
	if(getPositionx(img) <= (img.screen_width - img.width)) {
		x = getPositionx(img);
	} else {
		x = img.screen_width - img.width;
	}

	if(getPositiony(img) <= (img.screen_height - img.height)) {
		y = getPositiony(img);
	} else {
		y = img.screen_height - img.height;
	}
	al_draw_bitmap(img.image, x, y, 0);
}

void drawBackground(image img) {
	al_draw_bitmap(img.image, 0, 0, 0);
}

int *alocaPosition() {
	int *x = malloc(sizeof(int));
	return x;
}

void liberaPosition(int *x) {
	free(x);
}

void clearImage(image img) {
	liberaPosition(img.positionx);
	liberaPosition(img.positiony);
}

image newImage(ALLEGRO_BITMAP *img) {
	image imagem;
	imagem.image = img;
	imagem.width = getWidth(img);
	imagem.height = getHeight(img);
	imagem.positiony = alocaPosition();
	imagem.positionx = alocaPosition();
	setPositionx(imagem, imagem.width);
	setPositiony(imagem, imagem.height);
	int info[] = {0, 0};
	imagem.screen_width = info[0];
	imagem.screen_height = info[1];
	return imagem;
}
