#ifndef _CURSOR_H_
#define _CURSOR_H_

typedef struct _cursor{
	image imagem;
} cursor;

cursor newCursor(ALLEGRO_BITMAP *img);
void setCursorPosition(cursor img, int x, int y);
void setCursorPositionX(cursor img, int x);
void setCursorPositionY(cursor img, int y);
void drawCursor(cursor img);

#endif
