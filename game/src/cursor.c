#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "image.h"
#include "cursor.h"

// Constructor
cursor newCursor(ALLEGRO_BITMAP *img) {
	cursor newCursor;
	newCursor.imagem = newImage(img);
	return newCursor;
}

void drawCursor(cursor this) {
	draw(this.imagem);
}

void setCursorPositionX(cursor this, int x) {
	setPositionx(this.imagem, x);
}

void setCursorPositionY(cursor this, int y) {
	setPositiony(this.imagem, y);
}

void setCursorPosition(cursor this, int x, int y) {
	setPositionx(this.imagem, x);
	setPositiony(this.imagem, y);
}

