#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "camera.h"
#include "logger.h"
#include "global.h"
#include "image.h"
#include "cursor.h"

#define TRUE 1

char *testing_mode = "-t";
char *debug_mode = "-d";

int startGame(char **argv, global_var *global) {
	image background = newImage(al_load_bitmap("res/img/background_image.png"));
	while(TRUE){
		// gameMode representa como o jogo será executado
		// gameMode=0 será executado de forma padrão, apenas com registros de rotina.
		// gameMode=1 será executada com todos os eventos sendo registrados.
		// gameMode=2 será executado como debug, todos os eventos serão registrados e a imagem de
		// background não será mostrada
	
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
	
		// Imrpimindo elementos na tela
	
		drawBackground(background);
		al_flip_display();
	}
	return 1;
}

void showExemple(){
	logger("Tutorial.");
	fprintf(stderr, "Tutorial\n");
}
