#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "configure.h"
#include "camera.h"
#include "ranking.h"

typedef struct _global_var {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	config *configure;
	rank *ranking;
	camera *camera1;
	char *gamer;
	int gameMode;
} global_var;

#endif
