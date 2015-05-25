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

#define TRUE 1
#define FALSE 0

#define NORMAL_MODE 0
#define TESTING_MODE 1
#define DEBUG_MODE 2

#define ARQUIVO_CONFIG "config/configuracao.conf"
#define RANKING_FILE "res/ranking.txt"

#define CURSOR_ESQUERDO 0
#define CURSOR_DIREITO 1

#define POSITION_X 0
#define POSITION_Y 1

// Valores de rgb
#define RED   0
#define GREEN 1
#define BLUE  2

// Valores de hsv
#define HUE        0
#define SATURATION 1
#define LIGHTNESS  2

#endif
