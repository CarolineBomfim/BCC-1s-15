#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configure.h"
#include "logger.h"

#define DELIMITACAO "="
#define ESPACO_MEMORIA 100

// Atributos da janela
#define LARGURA "LARGURA"
#define ALTURA "ALTURA"

// Número de atualizações da tela por segundo
#define FPS "FRAMES_POR_SEGUNDO"
#define CASA_DECIMAL "CASA_DECIMAL"

// Altura limite para a a execução do evento
#define LIMIT_ACTION "LIMIT_ACTION"

// Número de objetos a serem rastreados
#define NUM_OBJ "NUMERO_DE_OBJETOS"

// Camera que deve ser carregada
#define CAM "CAM"

// Atributos dos objetos
#define H_MAX "H_MAX_"
#define H_MIN "H_MIN_"
#define S_MAX "S_MAX_"
#define S_MIN "S_MIN_"
#define V_MAX "V_MAX_"
#define V_MIN "V_MIN_"

// Salva o valor no arquivo de histórico para registros.
void registra_configuracao(config *configuracao) {
	char *detalhesConfiguracao = malloc(ESPACO_MEMORIA*sizeof(char));
	char *textoAuxiliar = malloc((10*ESPACO_MEMORIA)*sizeof(char));
	char *registro = malloc((10*ESPACO_MEMORIA)*sizeof(char));
	char **elementosRastreados = malloc(2*sizeof(char *));
	for (int i = 0; i < 2; i++) {
		elementosRastreados[i] = malloc(ESPACO_MEMORIA*sizeof(char));
		for (int j = 0; j < ESPACO_MEMORIA; ++j) {
			elementosRastreados[i][j] = ' ';
		}
	}
	int count = 0;

	sprintf(detalhesConfiguracao, 
	        "\n\n\n<=========>\n\nCamera %d\nLargura: %d\nAltura: %d\nNumero de objetos rastreado: %d\nFPS: %lf\n",
	        configuracao->cam, configuracao->largura, configuracao->altura, configuracao->num_obj, configuracao->fps);
	
	while(count < configuracao->num_obj) {
		sprintf(elementosRastreados[0],
		        "Maximo:\nH:\t%d\nS:\t%d\nV:\t%d\n", 
		        configuracao->atributos[count].h_max, 
		        configuracao->atributos[count].s_max,
		        configuracao->atributos[count].v_max);

		sprintf(elementosRastreados[1],
		        "Minimo:\nH:\t%d\nS:\t%d\nV:\t%d\n", 
		        configuracao->atributos[count].h_min,
		        configuracao->atributos[count].s_min,
		        configuracao->atributos[count].v_min);
	
		if(count == 0) {
			sprintf(textoAuxiliar, "<==Inicio objeto rastreado==>\n%s\n%s\n<==Fim objeto rastreado==>", 
		        elementosRastreados[0], elementosRastreados[1]);
		} else {
			sprintf(textoAuxiliar, "\n%s\n<==Inicio objeto rastreado==>\n%s\n%s\n<==Fim objeto rastreado==>", 
		        textoAuxiliar, elementosRastreados[0], elementosRastreados[1]);
		}
		count++;
	}
	
	sprintf(registro, "\n%s%s\n", detalhesConfiguracao, textoAuxiliar);
	for (int i = 0; i < 2; i++) {
		free(elementosRastreados[i]);
	}
	free(elementosRastreados);
	free(detalhesConfiguracao);
	free(registro);
	free(textoAuxiliar);
	logger(registro);
}

// Pega o valor referente ao prefixo da linha e o retorna como int
int pegar_valor(char *valor) {
	valor = strstr(valor, DELIMITACAO);
	valor = valor + strlen(DELIMITACAO);
	return atoi(valor);
}
// Pega o valor referente ao atributo da linha e o retorna como int
// Usado para os casos de h_max e h_min, além dos demais equivalentes
int pegar_atributo(char *prefixo, char *delimitar) {
	prefixo = strtok(prefixo, delimitar);
	return (atoi(prefixo)-1);
}

// Interpreta somente uma linha do arquivo de configuracção por vez e atribui os valores para as suas posições na variavel configure
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

	} else if(strcmp(prefixo, CASA_DECIMAL) == 0) {
		configure->valor_decimal = pegar_valor(valor);

	} else if(strcmp(prefixo, FPS) == 0) {
		configure->fps = pegar_valor(valor);

	} else if(strcmp(prefixo, CAM) == 0) {
		configure->cam = pegar_valor(valor);

	} else if(strcmp(prefixo, LIMIT_ACTION) == 0) {
		configure->limit_action = pegar_valor(valor);

	} else if(strcmp(prefixo, NUM_OBJ) == 0) {
		configure->num_obj = pegar_valor(valor);
		configure->atributos = malloc(configure->num_obj * sizeof(atributos));
	} else {

		char *auxiliar_atributo[strlen(prefixo) - 1];
		char *atributo = memcpy( auxiliar_atributo, prefixo, strlen(prefixo) - 1);

		if(strcmp(H_MAX, atributo) == 0) {
			// Associa cada elemento do hsv ao respectivo da configuração, por exemplo, H_MAX_1 será associado ao index 0 do vetor
			configure->atributos[pegar_atributo(prefixo, H_MAX)].h_max = pegar_valor(valor);
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
// Faz a leitura do arquivo e chama a função montar_configuracao para interpretar linha a linha 
config *ler_arquivo_configuracao(char *arquivo) {
	config *configure = malloc(sizeof(config));
	FILE *arquivo_carregado;
	char *linha = malloc(ESPACO_MEMORIA*sizeof(char));
	char *nova_linha = malloc(ESPACO_MEMORIA*sizeof(char));

	arquivo_carregado = fopen( arquivo, "r");
	
	if(!arquivo_carregado) {
		erro("Falha ao carregar arquivo de configuracao");
	}
	for(int i = 0; i < ESPACO_MEMORIA; i++) {
		linha[i] = ' ';
		nova_linha[i] = ' ';
	}
	while(fgets(linha, ESPACO_MEMORIA, arquivo_carregado) != NULL) {
		if( linha[0] != '#' ) {
			montar_configuracao(configure, memcpy( nova_linha, linha, strlen(linha) - 1));
			// memset está limpando o espaço de memoria para que não haja lixo entre uma linha a outra
			memset(nova_linha, 0, ESPACO_MEMORIA);
		}
	}
	free(linha);
	free(nova_linha);
	fclose(arquivo_carregado);
	registra_configuracao(configure);
	return configure;
}

void limpar_configuracao(config *c) {
	free(c->atributos);
	free(c);
}
