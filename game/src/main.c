#include "include.h"

#define ARQUIVO_CONFIG "../config/configuracao.conf"
#define ESPACO_MEMORIA 100
int main() {
	config *configuracao = ler_arquivo_configuracao(ARQUIVO_CONFIG);
	char aux[ESPACO_MEMORIA];
	camera *camera1 = camera_inicializa(0);
	sprintf(aux, "Camera: Altura= %d\nLargura= %d", camera1->altura, camera1->largura);
	registra(aux);
	camera_finaliza(camera1);

	return 0;
}
