#ifndef _TARGET_H_
#define _TARGET_H_


typedef struct _target {
	image imagem;
	bool show;
}target;

target newTarget(ALLEGRO_BITMAP *img);
void clearTarget(target this);
void drawTarget(target select);
void setPositionTarget(target select, int x, int y);
void drawTargets(target t1, target t2, target t3, target t4);

#endif
