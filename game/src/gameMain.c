#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "logger.h"
#include "global.h"
#include "image.h"
#include "cursor.h"
#include "target.h"
#include "track.h"
#include "musicGame.h"

int startGame(global_var *global) {
	logger("Iniciar jogo");
	camera_atualiza(global->camera1);
	// Faz a checagem para verificar se o fundo é igual.
	global->snapshot = getSnapshot(global);
	if(!global->snapshot) {
		erro("Erro ao copiar o primeiro frame.");
	}
	// Criando timer com 1 segundo espaçamento entre um evento e o outro. 
	/**
	 *
	 *
	 */
	// ALLEGRO_TIMER *timer  = al_create_timer(1.0);

	int **positions = malloc(global->configure->num_obj*sizeof(int *));
	for (int i = 0; i < global->configure->num_obj; ++i) {
		positions[i] = malloc(2*sizeof(int));
	}
	ALLEGRO_FONT *font				 = al_load_font("res/font/aardc.ttf", 36, 0);
	if(!font) {
		erro("Erro ao carregar fonte.");
	}

	image background 					 = newImage(al_load_bitmap("res/img/background_image.png"));
	target alvoAzul 					 = newTarget(al_load_bitmap("res/img/alvo_azul.png"));
	target alvoRosa 					 = newTarget(al_load_bitmap("res/img/alvo_rosa.png"));
	target alvoVerde 					 = newTarget(al_load_bitmap("res/img/alvo_verde.png"));
	target alvoVermelho 			 = newTarget(al_load_bitmap("res/img/alvo_vermelho.png"));
	ALLEGRO_BITMAP *buffer 		 = al_get_backbuffer(global->display);
	ALLEGRO_BITMAP *preview		 = al_create_sub_bitmap(buffer, 0, 0, global->configure->largura, global->configure->altura);
	
	// Musica
	ALLEGRO_SAMPLE_INSTANCE *sample;
	ALLEGRO_SAMPLE *sample_data= al_load_sample(global->music);
	// Carregando musica e as notas
	// music music_notes 					= readFileMusic(global->music_notes);
	if(!sample_data) {
		erro("Erro ao carregar musica.");
	}
	sample = al_create_sample_instance(NULL);
	if (!al_set_sample(sample, sample_data)) {
		erro("Erro ao associar a musica a instancia.");
	}
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

	setCursorPosition(right, global->configure->largura/2, global->configure->altura/2);
	setCursorPosition(left, global->configure->largura/2, global->configure->altura/2);

	if (global->gameMode == TESTING_MODE) {
		logger("Jogo iniciado em modo de teste. Todas as atividades serão registradas.");
	} else if(global->gameMode == DEBUG_MODE) {
		logger("Jogo iniciado em modo de debug. Todas as atividades serão registradas.");
	} else {
		logger("Jogo iniciado em modo padrão.");
	}

	// Iniciando audio
	al_set_sample_instance_playmode(sample, ALLEGRO_PLAYMODE_LOOP);
	al_play_sample(sample_data, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
	while(TRUE){
		// gameMode representa como o jogo será executado
		// gameMode=0 será executado de forma padrão, apenas com registros de rotina.
		// gameMode=1 será executada como teste, então background que não será mostrada.
		// gameMode=2 será executado como debug, mostrara mais informações no terminal
		// como a valor que estiver dentro do range rastreado, não será.

		// Executa o rastreamento e retorna a posição dos objetos rastrados
		track(global, positions);
		setCursorsPosition(left, right, positions);

		// Imrpimindo elementos na tela
		if(global->gameMode == NORMAL_MODE) {
			drawBackground(background);
		} else {
			camera_copia(global->camera1, global->camera1->quadro, preview);
			if(global->gameMode == DEBUG_MODE) {
				al_draw_filled_circle(positions[CURSOR_ESQUERDO][POSITION_X], positions[CURSOR_ESQUERDO][POSITION_Y], 50.0, al_map_rgb(0, 0, 255));
				al_draw_filled_circle(positions[CURSOR_DIREITO][POSITION_X], positions[CURSOR_DIREITO][POSITION_Y], 50.0, al_map_rgb(255, 0, 0));
			}
		}
		drawTargets(alvoAzul, alvoRosa, alvoVermelho, alvoVerde);
		drawTargets(alvoAzul2, alvoRosa2, alvoVermelho2, alvoVerde2);
		
		drawCursor(left);
		drawCursor(right);
		al_draw_textf(font, al_map_rgb(0, 255, 0), 30, (global->camera1->largura - 50), ALLEGRO_ALIGN_CENTER, "%s", global->music_name );
		al_draw_textf(font, al_map_rgb(0, 255, 0), 70, (global->camera1->largura - 50), ALLEGRO_ALIGN_CENTER, "%s", global->music_band );	
		al_flip_display();
	}
	al_destroy_sample(sample_data);
	for (int i = 0; i < global->configure->num_obj; ++i) {
		free(positions[i]);
	}
	free(positions);
	freeSnapshot(global->snapshot);
	return 1;
}
