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
	char *gamer, *music, *music_notes, *music_name, *music_band;
	int gameMode;
	unsigned char ***snapshot, ***hsv;
} global_var;

#define TRUE 1
#define FALSE 0

// Tipos de abertura do jogo
#define NORMAL_MODE 0
#define TESTING_MODE 1
#define DEBUG_MODE 2

// Arquivos fixos
#define ARQUIVO_CONFIG "config/configuracao.conf"
#define RANKING_FILE "res/ranking.txt"

// Configurações do arquivo de notas
#define TAMANHO_LINHA 4
#define TAMANHO_BLOCO 4

#define CURSOR_ESQUERDO 0
#define CURSOR_DIREITO 1

// Posição do cursor 
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


//Area de rastreio
#define INICIO_X 0
#define INICIO_Y 100
#define FIM_X 400
#define FIM_Y 480

//Diametro dos alvos
#define TARGET_HEIGHT 95
#define TARGET_WIDTH 95 

// Bloco dos alvos.
#define INICIO_AREA_ALVO_Y 360
#define FIM_AREA_ALVO_Y 455
#define INICIO_AREA_ALVO_X 15
#define FIM_AREA_ALVO_X 395

// Passa para a proxima linha da matriz
#define VELOCIDADE_PASSAGEM 15
#endif
