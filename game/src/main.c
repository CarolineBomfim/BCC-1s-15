#include "import.h"

#define ARQUIVO_CONFIG "config/configuracao.conf"

int main() {
	config *c = ler_arquivo_configuracao(ARQUIVO_CONFIG);
	printf("=======\n");
	printf("%d, %d, %d, %lf\n", c->largura, c->altura, c->num_obj, c->fps);
	printf("max\nh\t%d\ns\t%d\nv\t%d\n", c->atributos[0].h_max, c->atributos[0].s_max, c->atributos[0].v_max);
	printf("min\nh\t%d\ns\t%d\nv\t%d\n", c->atributos[0].h_min, c->atributos[0].s_min, c->atributos[0].v_min);
	printf("=======\n");
	printf("max\nh\t%d\ns\t%d\nv\t%d\n", c->atributos[1].h_max, c->atributos[1].s_max, c->atributos[1].v_max);
	printf("min\nh\t%d\ns\t%d\nv\t%d\n", c->atributos[1].h_min, c->atributos[1].s_min, c->atributos[1].v_min);

	return 0;
}
