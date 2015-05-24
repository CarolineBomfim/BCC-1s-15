#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "image.h"
#include "cursor.h"
#include "global.h"

// Construtor
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
	if(y > getImageHeight(this.imagem)) {
		setPositiony(this.imagem, getImageHeight(this.imagem));
	} else {
		setPositiony(this.imagem, y);
	}
}

void setCursorPosition(cursor this, int x, int y) {
	setCursorPositionX(this, x);
	setCursorPositionY(this, y);
}

void setCursorsPosition(cursor c1, cursor c2, int **positions){
	setCursorPosition(c1, positions[CURSOR_DIREITO][POSITION_X], positions[CURSOR_DIREITO][POSITION_Y]);
	setCursorPosition(c2, positions[CURSOR_ESQUERDO][POSITION_X], positions[CURSOR_ESQUERDO][POSITION_Y]);
}
