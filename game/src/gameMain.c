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

bool actionDetected(int **positions) {
	int ret = FALSE;	
	for(int i = 0; i < 2; i++ ) {
		if(INICIO_AREA_ALVO_Y <= positions[i][POSITION_Y] 
		   && positions[i][POSITION_Y] <= FIM_AREA_ALVO_Y) {
			if(INICIO_AREA_ALVO_X <= positions[i][POSITION_X]
			   && positions[i][POSITION_X] <= FIM_AREA_ALVO_X) {
				return (bool)TRUE;
			}
		}
	}
	return (bool)ret;
}

bool targetsInArea(target t1, target t2, target t3, target t4) {
	if( INICIO_AREA_ALVO_Y < getPositionTargety(t1) && getPositionTargety(t1) < FIM_AREA_ALVO_Y) {
		return (bool)TRUE;
	} else if(INICIO_AREA_ALVO_Y < getPositionTargety(t2) && getPositionTargety(t2) < FIM_AREA_ALVO_Y) {
		return (bool)TRUE;
	} else if(INICIO_AREA_ALVO_Y < getPositionTargety(t3) && getPositionTargety(t3) < FIM_AREA_ALVO_Y) {
		return (bool)TRUE;
	} else if(INICIO_AREA_ALVO_Y < getPositionTargety(t4) && getPositionTargety(t4) < FIM_AREA_ALVO_Y) {
		return (bool)TRUE;
	} 
	return (bool)FALSE;
}

int *getTargetInArea(target t1, target t2, target t3, target t4) {
	int *targets = malloc(4*sizeof(int));
	int aux = 0;
	if( INICIO_AREA_ALVO_Y < getPositionTargety(t1) && getPositionTargety(t1) < FIM_AREA_ALVO_Y) {
		targets[aux] = getPositionTargetx(t1);
	}
	if(INICIO_AREA_ALVO_Y < getPositionTargety(t2) && getPositionTargety(t2) < FIM_AREA_ALVO_Y) {
		aux++;
		targets[aux] = getPositionTargetx(t2);
	}
	if(INICIO_AREA_ALVO_Y < getPositionTargety(t3) && getPositionTargety(t3) < FIM_AREA_ALVO_Y) {
		aux++;
		targets[aux] = getPositionTargetx(t3);
	}
	if(INICIO_AREA_ALVO_Y < getPositionTargety(t4) && getPositionTargety(t4) < FIM_AREA_ALVO_Y) {
		aux++;
		targets[aux] = getPositionTargetx(t4);
	}
	return targets;
}

int startGame(global_var *global) {
	bool unespectedStop = FALSE;
	logger("Iniciar jogo");
	camera_atualiza(global->camera1);
	// Faz a checagem para verificar se o fundo é igual.
	global->snapshot = getSnapshot(global);
	// Para evitar alocar e desalocar uma matriz o todo novo ciclo, utilizar uma unica matriz 
	// e altarar os valores a cada novo ciclo
	global->hsv = getSnapshot(global);
	if(!global->snapshot || !global->hsv) {
		erro("Erro ao copiar o primeiro frame.");
	}

	// 0.5 segundo
	ALLEGRO_TIMER *timer  = al_create_timer(0.5);


	// Prepara fila de eventos 
	al_register_event_source(global->event_queue, al_get_timer_event_source(timer));
	al_register_event_source(global->event_queue, al_get_display_event_source(global->display));



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
	target error1				 			 = newTarget(al_load_bitmap("res/img/errorImage.png"));
	target error2				 			 = newTarget(al_load_bitmap("res/img/errorImage.png"));
	target error3				 			 = newTarget(al_load_bitmap("res/img/errorImage.png"));
	target error4				 			 = newTarget(al_load_bitmap("res/img/errorImage.png"));
	ALLEGRO_BITMAP *buffer 		 = al_get_backbuffer(global->display);
	ALLEGRO_BITMAP *preview		 = al_create_sub_bitmap(buffer, 0, 0, global->configure->largura, global->configure->altura);

	// Colors
	ALLEGRO_COLOR white = al_map_rgb(255,255,255);
	ALLEGRO_COLOR black = al_map_rgb(0,0,0);
	ALLEGRO_COLOR red = al_map_rgb(237,23,97);
	ALLEGRO_COLOR green = al_map_rgb(10,212,153);
	ALLEGRO_COLOR blue = al_map_rgb(55,47,223);
	ALLEGRO_COLOR pink = al_map_rgb(228,65,220);

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
	setPositionTarget(alvoAzul, INICIO_AREA_ALVO_X, 0);
	setPositionTarget(alvoRosa, INICIO_AREA_ALVO_X + TARGET_WIDTH, 0);
	setPositionTarget(alvoVermelho, INICIO_AREA_ALVO_X + 2*TARGET_WIDTH, 0);
	setPositionTarget(alvoVerde, INICIO_AREA_ALVO_X + 3*TARGET_WIDTH, 0);

	// Duplicando alvo para ele poder ser impresso duas vezes simultaneamete na tela
	target alvoAzul2 = alvoAzul;
	target alvoRosa2 = alvoRosa;
	target alvoVerde2 = alvoVerde;
	target alvoVermelho2 = alvoVermelho;

	// Definindo propriedades das imagens de erro
	setPositionTarget(error1, INICIO_AREA_ALVO_X, INICIO_AREA_ALVO_Y);
	setPositionTarget(error2, INICIO_AREA_ALVO_X + TARGET_WIDTH, INICIO_AREA_ALVO_Y);
	setPositionTarget(error3, INICIO_AREA_ALVO_X + 2*TARGET_WIDTH, INICIO_AREA_ALVO_Y);
	setPositionTarget(error4, INICIO_AREA_ALVO_X + 3*TARGET_WIDTH, INICIO_AREA_ALVO_Y);
	//Carregando cursores
	cursor left = newCursor(al_load_bitmap("res/img/cursor_left.png"));
	cursor right = newCursor(al_load_bitmap("res/img/cursor_right.png"));	
	// Os cursores devem ficar a baixo da linha que define a ação
	setCursorPosition(right, global->configure->largura/2, global->configure->altura - 120);
	setCursorPosition(left, global->configure->largura/2, global->configure->altura - 120);

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

	// Inicia o timer
	al_start_timer(timer);

	int timerCounting = 0;

	// Para usar no rand 
	time_t varTime;
	unsigned randResult;
	while(TRUE){
		ALLEGRO_EVENT event;
		al_wait_for_event(global->event_queue, &event);

		if(event.type == ALLEGRO_EVENT_TIMER) {
			timerCounting++;
			// Limpa os erros
			hideTarget(error1);
			hideTarget(error2);
			hideTarget(error3);
			hideTarget(error4);
		}
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			unespectedStop = TRUE;
			break;
		}

		// Encerra o laço até quando a música chega ao fim, solução temporaria
		// 600 = tempoDaMusica*2
		if(timerCounting == 600) {
			break;
		}
		// Temporario até a resolução do leito do arquivo com as notas
		if(timerCounting%5 == 0 ) {
			srand((unsigned) time(&varTime));
			randResult = rand() % 40;
			if((randResult % 4) == 0) {
				showTarget(alvoAzul);
			}
			randResult = rand() % 40;
			if((randResult % 4) == 0) {
				showTarget(alvoRosa);
			}
			randResult = rand() % 40;
			if((randResult % 4) == 0) {
				showTarget(alvoVermelho);
			}
			randResult = rand() % 40;
			if((randResult % 4) == 0) {
				showTarget(alvoVerde);
			}
		}

		// gameMode representa como o jogo será executado
		// gameMode=0 será executado de forma padrão, apenas com registros de rotina.
		// gameMode=1 será executada como teste, então background que não será mostrada.
		// gameMode=2 será executado como debug, mostrara mais informações no terminal
		// como a valor que estiver dentro do range rastreado, não será.

		// Executa o rastreamento e retorna a posição dos objetos rastrados
		track(global, positions);
		setCursorsPosition(global, left, right, positions);

		// Imrpimindo elementos na tela
		if(global->gameMode == NORMAL_MODE) {
			drawBackground(background);
		} else {
			camera_copia(global->camera1, global->camera1->quadro, preview);
			// Define a linha do bloco de ação
			al_draw_line((double)FIM_AREA_ALVO_X, 0,(double)FIM_AREA_ALVO_X,global->configure->altura,black, 2);
			al_draw_line((double)INICIO_AREA_ALVO_X, 0,(double)INICIO_AREA_ALVO_X,global->configure->altura,black, 2);
			
			// Trilho dos alvos
			al_draw_line((double)(INICIO_AREA_ALVO_X + TARGET_WIDTH), 0,(double)(INICIO_AREA_ALVO_X + TARGET_WIDTH),global->configure->altura,black, 1);			
			al_draw_line((double)(INICIO_AREA_ALVO_X + 2*TARGET_WIDTH), 0,(double)(INICIO_AREA_ALVO_X + 2*TARGET_WIDTH),global->configure->altura,black, 1);
			al_draw_line((double)(INICIO_AREA_ALVO_X + 3*TARGET_WIDTH), 0,(double)(INICIO_AREA_ALVO_X + 3*TARGET_WIDTH),global->configure->altura,black, 1);
		}

		// Area relevante da detecção
		if ( targetsInArea(alvoAzul, alvoRosa, alvoVermelho, alvoVerde)
			|| targetsInArea(alvoAzul2, alvoRosa2, alvoVermelho2, alvoVerde2) ) {
			// Current em int para verificar a posição dos alvos, como a posião em x é fixa não há problema
			
			int *current = getTargetInArea(alvoAzul, alvoRosa, alvoVermelho, alvoVerde);
			if(actionDetected(positions)) {
				int i = 0;
				// Mostra o acerto para cada target individualmente
				while(current[i]){
					if(current[i] == getPositionTargetx(alvoAzul)
					   || current[i] == getPositionTargetx(alvoAzul2)) {
						al_draw_filled_circle((double)INICIO_AREA_ALVO_X, (double)INICIO_AREA_ALVO_Y, TARGET_WIDTH, blue);
					}

					if(current[i] == getPositionTargetx(alvoRosa)
	           || current[i] == getPositionTargetx(alvoRosa2)) {
						al_draw_filled_circle((double)INICIO_AREA_ALVO_X + TARGET_WIDTH, (double)INICIO_AREA_ALVO_Y, TARGET_WIDTH, pink);
					}
					
					if(current[i] == getPositionTargetx(alvoVermelho)
	           || current[i] == getPositionTargetx(alvoVermelho2)) {
						al_draw_filled_circle((double)INICIO_AREA_ALVO_X + 2*TARGET_WIDTH, (double)INICIO_AREA_ALVO_Y, TARGET_WIDTH, red);
					}
					
					if (current[i] == getPositionTargetx(alvoVerde)
	            || current[i] == getPositionTargetx(alvoVerde2)) {
						al_draw_filled_circle((double)INICIO_AREA_ALVO_X + 3*TARGET_WIDTH, (double)INICIO_AREA_ALVO_Y, TARGET_WIDTH, green);
					}
				}
			} else {
				int i = 0;
				// Mostra o erro para cada target que esteja na zona ao mesmo tempo que os cursores não estão
				while(current[i]) {
					if(current[i] == getPositionTargetx(alvoAzul)
					   || current[i] == getPositionTargetx(alvoAzul2)) {
						showTarget(error1);
					}
					if(current[i] == getPositionTargetx(alvoRosa)
	           || current[i] == getPositionTargetx(alvoRosa2)) {
						showTarget(error2);
					}
					if(current[i] == getPositionTargetx(alvoVermelho)
	           || current[i] == getPositionTargetx(alvoVermelho2)) {
						showTarget(error3);
					}
					if (current[i] == getPositionTargetx(alvoVerde)
	            || current[i] == getPositionTargetx(alvoVerde2)) {
						showTarget(error4);
					}
					i++;
				}
			}
			free(current);
		}

		// Efeito cascata dos alvos
		cascateTargets(global, alvoAzul, alvoRosa, alvoVermelho, alvoVerde);
		cascateTargets(global, alvoAzul2, alvoRosa2, alvoVermelho2, alvoVerde2);

		// Desenha na tela tudo que é padrão para todos os modos de jogo

		// Posição real do objeto detectado
		for (int k = 0; k < global->configure->num_obj; k++) {
			if(k == CURSOR_ESQUERDO) {
				al_draw_circle(positions[CURSOR_ESQUERDO][POSITION_X], positions[CURSOR_ESQUERDO][POSITION_Y], 30.0, blue, 2.0);
			} else if(k == CURSOR_DIREITO) {
				al_draw_circle(positions[CURSOR_DIREITO][POSITION_X], positions[CURSOR_DIREITO][POSITION_Y], 30.0, red, 2.0);
			}
		}

		al_draw_line((double)INICIO_AREA_ALVO_X, (double)INICIO_AREA_ALVO_Y,(double)FIM_AREA_ALVO_X,(double)INICIO_AREA_ALVO_Y,white, 2);
		al_draw_line((double)INICIO_AREA_ALVO_X, (double)FIM_AREA_ALVO_Y,(double)FIM_AREA_ALVO_X,(double)FIM_AREA_ALVO_Y,white, 2);

		// Informações da musica
		al_draw_textf(font, green, (global->camera1->largura/2) + 100, 30, ALLEGRO_ALIGN_LEFT, "%s", global->music_name );
		al_draw_textf(font, green, (global->camera1->largura/2) + 180, 70, ALLEGRO_ALIGN_LEFT, "%s", global->music_band );

		drawTargets(alvoAzul, alvoRosa, alvoVermelho, alvoVerde);
		drawTargets(alvoAzul2, alvoRosa2, alvoVermelho2, alvoVerde2);
		drawTargets(error1, error2, error3, error4);

		// Cursor para mostrar em  qual alvo está o objeto
		drawCursor(left);
		drawCursor(right);
		al_flip_display();
	}
	al_destroy_sample(sample_data);
	for (int i = 0; i < global->configure->num_obj; ++i) {
		free(positions[i]);
	}
	free(positions);
	freeSnapshot(global, global->snapshot);
	freeSnapshot(global, global->hsv);
	if(unespectedStop) {
		return (-1);
	}
	return 1;
}
