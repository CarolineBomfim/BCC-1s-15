#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "configure.h"
#include "camera.h"

typedef struct _global_var {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	config *configure;
	char *gamer;
	camera *camera1;
	int gameMode;
}global_var;

#endif
