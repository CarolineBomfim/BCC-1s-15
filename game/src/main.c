#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "camera.h"
#include "global.h"
#include "configure.h"
#include "gameMain.h"
#include "ranking.h"
#include "initialMenu.h"
#include "logger.h"

#define ARQUIVO_CONFIG "config/configuracao.conf"
#define ESPACO_MEMORIA 100
#define FALSE 0
#define TRUE 1

void gameExit(global_var *global);

int main(int argc, char **argv) {
	al_init();

	if(!al_init_image_addon()) {
		erro("Falha ao carregar biblioteca de images.");
	}

<<<<<<< HEAD
	if(!al_install_mouse()) {
		erro("Falha ao instalar mouse.");
	}
=======

	al_init_font_addon();
	

>>>>>>> c710fb7e06bc7d4a28dfc1ecb8eaa2836f09a91a
	config *configuracao = ler_arquivo_configuracao(ARQUIVO_CONFIG);
	global_var *global = malloc(sizeof(global_var));

	char aux[ESPACO_MEMORIA];
	int trying = 0;

	//global->camera1 = camera_inicializa(0);

	//sprintf(aux, "Camera: Altura= %d\n\t\t\tLargura= %d", 
	      //  global->camera1->altura, global->camera1->largura);
	logger(aux);
	sprintf(aux, "Config: Altura= %d\n\t\t\tLargura= %d", 
	        configuracao->altura, configuracao->largura);
	logger(aux);
	
	global->display = al_create_display(configuracao->largura, configuracao->altura);
	global->event_queue = al_create_event_queue();

	if(!global->event_queue) {
		erro("Falha ao criar fila de eventos");
	}

     

	if(!argv) {
		argv[1] = "-n";
	}

	if(!global->display) {
		erro("Falha ao criar arquivo display");
	}

	while(TRUE) {
		switch (initialMenu(trying, global)) {
			case 0:
				trying += startGame(argv, global);
				fprintf(stderr, "Saiu.\n" );
				break;

			case 1:
				showRanking();
				break;

			case 2:
				showExemple();
				break;

			default:
				gameExit(global);

		}
	}
	return 0;
}

void gameExit(global_var *global) {
	al_destroy_display(global->display);
	//camera_finaliza(global->camera1);
	free(global);
	logger("Sair do jogo");
	exit(EXIT_SUCCESS);
}


