#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "logger.h"
#include "global.h"
#include "image.h"
#include "cursor.h"
#include "target.h"
#include "audio.h"
#include "track.h"
#include "musicGame.h"

int startGame(global_var *global) {
	logger("Iniciar jogo");

	// Criando timer com 1 segundo espaçamento entre um evento e o outro. 
	ALLEGRO_TIMER *timer  = al_create_timer(1.0);

	int **positions = malloc(global->configure->num_obj*sizeof(int *));
	
	for (int i = 0; i < global->configure->num_obj; ++i) {
		positions[i] = malloc(2*sizeof(int));
	}

	image background 				= newImage(al_load_bitmap("res/img/background_image.png"));
	target alvoAzul 				= newTarget(al_load_bitmap("res/img/alvo_azul.png"));
	target alvoRosa 				= newTarget(al_load_bitmap("res/img/alvo_rosa.png"));
	target alvoVerde 				= newTarget(al_load_bitmap("res/img/alvo_verde.png"));
	target alvoVermelho 		= newTarget(al_load_bitmap("res/img/alvo_vermelho.png"));
	ALLEGRO_BITMAP *buffer 	= al_get_backbuffer(global->display);
	ALLEGRO_BITMAP *preview	= al_create_sub_bitmap(buffer, 0, 0, global->configure->largura, global->configure->altura);

	// Carregando musica e as notas
	// audio currentAudio 	= newAudio(al_load_audio_stream("res/song/bang-your-head.ogg", 4, 1024));
	// music music_notes 					= readFileMusic("res/song/bang-your-head.notes");
	// Organizando posições do alvo, o diametro de cada alvo é de 95px
	setPositionTarget(alvoAzul, 15, 0);
	setPositionTarget(alvoRosa, 110, 0);
	setPositionTarget(alvoVermelho, 205, 0);
	setPositionTarget(alvoVerde, 300, 0);

	// Duplicando alvo para ele poder ser impresso duas vezes simultaneamete na tela
	target alvoAzul2 = alvoAzul;
	target alvoRosa2 = alvoRosa;
	target alvoVerde2 = alvoVerde;
	target alvoVermelho2 = alvoVermelho;

	//Carregando cursores
	cursor left = newCursor(al_load_bitmap("res/img/cursor_left.png"));
	cursor right = newCursor(al_load_bitmap("res/img/cursor_right.png"));	

	if (global->gameMode == TESTING_MODE) {
		logger("Jogo iniciado em modo de teste. Todas as atividades serão registradas.");
	} else if(global->gameMode == DEBUG_MODE) {
		logger("Jogo iniciado em modo de debug. Todas as atividades serão registradas.");
	} else {
		logger("Jogo iniciado em modo padrão.");
	}

	// Iniciando audio
	// play(currentAudio);

	while(TRUE){
		// gameMode representa como o jogo será executado
		// gameMode=0 será executado de forma padrão, apenas com registros de rotina.
		// gameMode=1 será executada com todos os eventos sendo registrados.
		// gameMode=2 será executado como debug, todos os eventos serão registrados e a imagem de
		// background não será mostrada

		// Executa o rastreamento e retorna a posição dos objetos rastrados
		track(global, positions);
		setCursorsPosition(right, left, positions);

		// Imrpimindo elementos na tela
		if(global->gameMode == NORMAL_MODE) {
			drawBackground(background);
		} else {
			camera_copia(global->camera1, global->camera1->quadro, preview);
		}
		drawTargets(alvoAzul, alvoRosa, alvoVermelho, alvoVerde);
		drawTargets(alvoAzul2, alvoRosa2, alvoVermelho2, alvoVerde2);
		drawCursor(left);
		drawCursor(right);
		al_flip_display();
	}

	for (int i = 0; i < global->configure->num_obj; ++i) {
		free(positions[i]);
	}
	free(positions);
	return 1;
}

void showExemple(){
	logger("Tutorial.");
	fprintf(stderr, "Tutorial\n");
}


/**
	
		if(count == 10) {
			alvoAzul.show 		= FALSE;
			alvoRosa.show 		= FALSE;
			alvoVerde.show 		= FALSE;
			alvoVermelho.show = FALSE;
			count = 0;
		}

		for( int i = 0; i < ((int)sizeof(music.music[bloco])); ++i) {
			for(int j = 0; j < ((int)sizeof(music.music[bloco][i])); ++j) {
				if(music.music[bloco][i][j] == 1 && j == 0) {
					alvoAzul.show = TRUE;
				} else {
					alvoAzul.show = FALSE;
				}
				if(music.music[bloco][i][j] == 1 && j == 1) {
					alvoRosa.show = TRUE;
				} else {
					alvoRosa.show = FALSE;
				}
				if(music.music[bloco][i][j] == 1 && j == 2) {
					alvoVerde.show = TRUE;
				} else {
					alvoVerde.show = FALSE;
				}
				if(music.music[bloco][i][j] == 1 && j == 3) {
					alvoVermelho.show = TRUE;
				} else {
					alvoVermelho.show = FALSE;
				}
			}
		}


**/
