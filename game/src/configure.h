#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

typedef struct _atributos{
	int h_min;
	int h_max;
	int s_min;
	int s_max;
	int v_min;
	int v_max;
}atributos;

typedef struct _config {
	int largura, altura, num_obj, limit_action, valor_decimal, cam, cascateSpeed;
	double fps;
	atributos *atributos;
}config;


config *ler_arquivo_configuracao(char *arquivo);
void limpar_configuracao(config *c);

#endif
