#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "image.h"

cursor newCursor(ALLEGRO_BITMAP *img) {
	cursor newCursor;
	newCursor.imagem = newImage(img);
	return newCursor;
}

void setCursorPosition(cursor img, int x, int y) {
	setPositionx(select.imagem, x);
	setPositiony(select.imagem, y);
}
void setCursorPositionX(cursor img, int x) {
	setPositionx(select.imagem, x);
}

void setCursorPositionY(cursor img, int y) {
	setPositiony(select.imagem, y);
}

void drawCursor(cursor img) {
	draw(img.imagem);
}
