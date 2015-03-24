#include <stdio.h>
#include <stdlib.h>
#include "camera.h"
#include "configure.h"
#include "gameMain.h"
#include "ranking.h"
#include "initialMenu.h"
#include "logger.h"

#define ARQUIVO_CONFIG "config/configuracao.conf"
#define ESPACO_MEMORIA 100
#define FALSE 0
#define TRUE 1

void gameExit();
int main(int argc, char **argv) {

	config *configuracao = ler_arquivo_configuracao(ARQUIVO_CONFIG);
	char aux[ESPACO_MEMORIA];
	camera *camera1 = camera_inicializa(0);

	sprintf(aux, "Camera: Altura= %d\nLargura= %d", camera1->altura, camera1->largura);
	logger(aux);

	int trying = 0;

	while(TRUE) {
		switch (initialMenu(trying)) {
			case 0:
				trying += startGame(argv);
				break;

			case 1:
				showRanking();
				break;

			case 2:
				showExemple();
				break;

			default:
				gameExit();
		}
	}

	camera_finaliza(camera1);

	return 0;
}

void gameExit() {
	logger("Sair do jogo");
	exit(EXIT_SUCCESS);
}