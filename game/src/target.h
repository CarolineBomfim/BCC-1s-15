#ifndef _TARGET_H_
#define _TARGET_H_


typedef struct _target {
	image imagem;
	int *show;
}target;

target newTarget(ALLEGRO_BITMAP *img);
void clearTarget(target this);
void drawTarget(target this);
int getPositionTargetx(target this);
int getPositionTargety(target this);
void setPositionTargety(target this, int y);
void setPositionTarget(target this, int x, int y);
void drawTargets(target t1, target t2, target t3, target t4);
void cascateTargets(global_var *global, target t1, target t2, target t3, target t4);
void showTarget(target this);
void hideTarget(target this);
#endif
