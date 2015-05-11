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
	setCursorPosition(c1, positions[0][0], positions[0][1]);
	setCursorPosition(c2, positions[1][0], positions[1][1]);
}
