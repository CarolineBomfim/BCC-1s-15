#include "import.h"

#define DELIMITACAO "="
#define ESPACO_MEMORIA 100

// Atributos da janela
#define LARGURA "LARGURA"
#define ALTURA "ALTURA"

// Número de atualizações da tela por segundo
#define FPS "FRAMES_POR_SEGUNDO"

// Número de objetos a serem rastreados
#define NUM_OBJ "NUMERO_DE_OBJETOS"

// Atributos dos objetos
#define H_MAX "H_MAX_"
#define H_MIN "H_MIN_"
#define S_MAX "S_MAX_"
#define S_MIN "S_MIN_"
#define V_MAX "V_MAX_"
#define V_MIN "V_MIN_"

int pegar_valor(char *valor) {
	valor = strstr(valor, DELIMITACAO);
	valor = valor + strlen(DELIMITACAO);
	return atoi(valor);
}

int pegar_atributo(char *prefixo, char *delimitar) {
	prefixo = strtok(prefixo, delimitar);
	return (atoi(prefixo)-1);
}

void montar_configuracao(config *configure, char *linha) {
	char *auxiliar_prefixo[ESPACO_MEMORIA];
	char *prefixo = memcpy( auxiliar_prefixo, linha, ESPACO_MEMORIA);
	char *auxiliar_valor[ESPACO_MEMORIA];
	char *valor = memcpy( auxiliar_valor, linha, ESPACO_MEMORIA);
	
	prefixo = strtok(prefixo, DELIMITACAO);
	
	if(strcmp(prefixo, LARGURA) == 0) {
		configure->largura = pegar_valor(valor);

	} else if(strcmp(prefixo, ALTURA) == 0) {
		configure->altura = pegar_valor(valor);

	} else if(strcmp(prefixo, FPS) == 0) {
		configure->fps = pegar_valor(valor);

	} else if(strcmp(prefixo, NUM_OBJ) == 0) {
		configure->num_obj = pegar_valor(valor);
		configure->atributos = malloc(configure->num_obj * sizeof(atributos));
	} else {

		char *auxiliar_atributo[strlen(prefixo) - 1];
		char *atributo = memcpy( auxiliar_atributo, prefixo, strlen(prefixo) - 1);

		if(strcmp(H_MAX, atributo) == 0) {
			configure->atributos[pegar_atributo(prefixo, H_MAX)].h_max = pegar_valor(valor);
			printf("%d\n", pegar_atributo(prefixo, H_MAX));
		} else if(strcmp(H_MIN, atributo) == 0) {
			configure->atributos[pegar_atributo(prefixo, H_MIN)].h_min = pegar_valor(valor);
		}
		if(strcmp(S_MAX, atributo) == 0) {
			configure->atributos[pegar_atributo(prefixo, S_MAX)].s_max = pegar_valor(valor);
		} else if(strcmp(S_MIN, atributo) == 0) {
			configure->atributos[pegar_atributo(prefixo, S_MIN)].s_min = pegar_valor(valor);
		}
		if(strcmp(V_MAX, atributo) == 0) {
			configure->atributos[pegar_atributo(prefixo, V_MAX)].v_max = pegar_valor(valor);
		} else if(strcmp(V_MIN, atributo) == 0) {
			configure->atributos[pegar_atributo(prefixo, V_MIN)].v_min = pegar_valor(valor);
		}

	}

}

config *ler_arquivo_configuracao(char *arquivo) {
	config *configure = malloc(sizeof(config));
	FILE *arquivo_carregado;
	char *linha = malloc(ESPACO_MEMORIA*sizeof(char));
	char *nova_linha[ESPACO_MEMORIA];

	arquivo_carregado = fopen( arquivo, "r");
	
	if(!arquivo_carregado) {
		printf("Falha ao carregar arquivo\n");
		exit(EXIT_FAILURE);
	}

	while(fgets(linha, ESPACO_MEMORIA, arquivo_carregado) != NULL) {
		if( linha[0] != '#' ) {
			montar_configuracao(configure, memcpy( nova_linha, linha, strlen(linha) - 1));
			memset(nova_linha, 0, ESPACO_MEMORIA);
		}
	}
	free(linha);
	fclose(arquivo_carregado);
	return configure;
}

void limpar_configuracao(config *c) {
	free(c->atributos);
	free(c);
}
