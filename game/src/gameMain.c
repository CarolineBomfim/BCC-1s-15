#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "camera.h"
#include "logger.h"
#include "global.h"
#include "image.h"
#include "cursor.h"
#include "target.h"
#include "musicGame.h"

#define TRUE 1
#define FALSE 0

char *testing_mode = "-t";
char *debug_mode = "-d";

int startGame(char **argv, global_var *global) {
	image background 			= newImage(al_load_bitmap("res/img/background_image.png"));
	target alvoAzul 			= newTarget(al_load_bitmap("res/img/alvo_azul.png"));
	target alvoRosa 			= newTarget(al_load_bitmap("res/img/alvo_rosa.png"));
	target alvoVerde 			= newTarget(al_load_bitmap("res/img/alvo_verde.png"));
	target alvoVermelho 	= newTarget(al_load_bitmap("res/img/alvo_vermelho.png"));
	music music 					= readFileMusic("res/song/bang-your-head-notes.txt");
	int laco = 10, count 	= 0;

	int gameMode = 0;
	if (argv[1] == testing_mode) {
		logger("Jogo iniciado em modo de teste. Todas as atividades serão registradas.");
		gameMode = 1;
	} else if(argv[1] == debug_mode) {
		logger("Jogo iniciado em modo de debug. Todas as atividades serão registradas.");
		gameMode = 2;
	} else {
		logger("Jogo iniciado em modo padrão.");
	}
	int bloco = 0;
	while(TRUE){
		// gameMode representa como o jogo será executado
		// gameMode=0 será executado de forma padrão, apenas com registros de rotina.
		// gameMode=1 será executada com todos os eventos sendo registrados.
		// gameMode=2 será executado como debug, todos os eventos serão registrados e a imagem de
		// background não será mostrada
	
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

		// Imrpimindo elementos na tela
		drawBackground(background);
		drawTargets(alvoAzul, alvoRosa, alvoVermelho, alvoVerde);
		al_flip_display();
		count++;
	}
	return 1;
}

void showExemple(){
	logger("Tutorial.");
	fprintf(stderr, "Tutorial\n");
}
