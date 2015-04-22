#ifndef _CURSOR_H_
#define _CURSOR_H_

typedef struct _cursor{
	image imagem;
} cursor;

cursor newCursor(ALLEGRO_BITMAP *img);
void drawCursor(cursor this);
void setCursorPositionX(cursor this, int x);
void setCursorPositionY(cursor this, int y);
void setCursorPosition(cursor this, int x, int y);

#endif
