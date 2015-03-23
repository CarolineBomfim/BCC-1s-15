#include "include.h"

#define ARQUIVO_CONFIG "../config/configuracao.conf"
#define ESPACO_MEMORIA 100
#define FALSE 0
#define TRUE 1

int main(int argc, char **argv) {

	config *configuracao = ler_arquivo_configuracao(ARQUIVO_CONFIG);
	char aux[ESPACO_MEMORIA];
	camera *camera1 = camera_inicializa(0);

	sprintf(aux, "Camera: Altura= %d\nLargura= %d", camera1->altura, camera1->largura);
	registra(aux);

	int tentativas = 0;

	while(TRUE) {
		switch menuInicial(tentativas) {
			case 0:
				tentativas += iniciarJogo(argv);
				break;

			case 1:
				mostrarRanking();
				break;

			case 2:
				mostrarTutorial();
				break;

			default:
				sair();
		}
	}

	camera_finaliza(camera1);

	return 0;
}
