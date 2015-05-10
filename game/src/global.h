#ifndef _GLOBAL_H_
#define _GLOBAL_H_

typedef struct _global_var {
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *event_queue;
	char *gamer;
	camera *camera1;
}global_var;
#endif
