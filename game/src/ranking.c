#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "ranking.h"
#include "logger.h"

#define DELIMITACAO ","
#define ESPACO_MEMORIA 50

void troca(rank *v, int i, int j) {
	rank aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

int getSizeRank(rank *ranking) {
	int i = 0;
	bool _while = TRUE;
	while(_while) {
		if(!ranking[i].record) {
			_while = FALSE;
			break;
		}
		printf("=====;;;>>>%s", ranking[i].name);
		i++;
	}

	// Aumentar 1 retorna o tamanho do vetor com contagem começando do 1
	i++;
	return 3;
}

void insertionSort(rank *v, int tam) {
	int i, j;
	rank selected;
	for ( i = 1; i < tam; i++) {
		selected = v[i];
		j = i - 1;
		while((j >= 0) && (selected.record < v[j].record)) {
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = selected;
	}
}

rank *ordenaRank(rank *ranking) {
	insertionSort(ranking, getSizeRank(ranking));
	return ranking;
}

int getSizeFile(char *arquivo) {
	FILE *arq;
	char *linha = malloc(ESPACO_MEMORIA*sizeof(char));
	int tam = 0;
	arq = fopen( arquivo, "r");
	while(fgets(linha, ESPACO_MEMORIA, arq) != NULL) {
		tam++;
	}
	fclose(arq);
	free(linha);
	// Ultima linha do arquivo é nula
	return tam-1;
}

int getRecord(char *linha) {
	char *record;
	record = memchr(linha, ',', strlen(linha));
	// Limpar Delimitacao da string
	record[0] = ' ';
	return atoi(record);
}

char *getName(char *linha) {
	char *aux = strtok(linha, DELIMITACAO);
	char *shortName = malloc(strlen(aux) * sizeof(char));
	shortName = memcpy(shortName, aux, strlen(aux));
	return shortName;
}

// Interpreta somente uma linha do arquivo de configuracção por vez e atribui os valores para as suas posições na variavel configure
rank montar_ranking(char *linha) {
	char *a1[ESPACO_MEMORIA];
	char *nomeAux = memcpy(a1, linha, ESPACO_MEMORIA);
	char *a2[ESPACO_MEMORIA];
	char *recordAux = memcpy(a2, linha, ESPACO_MEMORIA);
	rank current;
	int record = getRecord(recordAux);
	current.record = record;
	char *name = getName(nomeAux);
	current.name = name;
	return current;
}

// Faz a leitura do arquivo e chama a função montar_ranking para interpretar linha a linha e alocar cada
rank *ler_ranking(char *caminho_arquivo) {
	int sizeFile = getSizeFile(caminho_arquivo);
	int i = 0;
	rank *ranking = malloc(sizeFile*sizeof(rank));
	FILE *arquivo;
	char *linha = malloc(ESPACO_MEMORIA*sizeof(char));
	char *nova_linha[ESPACO_MEMORIA];
	arquivo = fopen( caminho_arquivo, "r");
	
	if(!arquivo) {
		logger("Ranking vazio");
	} else {
		while(fgets(linha, ESPACO_MEMORIA, arquivo) != NULL && i < sizeFile) {
			if(65 < (int)linha[0] && (int)linha[0] < 128){
				ranking[i] = montar_ranking(memcpy( nova_linha, linha, strlen(linha) - 1));
				i++;
			}

			// memset está limpando o espaço de memoria para que não haja lixo entre uma linha a outra
			memset(nova_linha, 0, ESPACO_MEMORIA);
			memset(linha, 0, ESPACO_MEMORIA);
		}
	}

	free(linha);
	fclose(arquivo);
	return ranking;
}

void criarRankingFile(rank *ranking, char *arquivo) {
	int tam = getSizeRank(ranking);
	// ordenaRank(ranking);
	FILE *file;
	file = fopen(arquivo, "w");
	for (int i = 0; i < tam; ++i) {
		fprintf(file, "%s,%d\n", ranking[i].name, ranking[i].record );
	}
	fclose(file);
}

void showRanking(rank *ranking) {
	logger("Show ranking");
	int tam = getSizeRank(ranking);
	printf("%d\n", tam);
	for (int i = 0; i < tam; i++) {
		printf("(%d) - (%s)(%d)\n", i,	ranking[i].name, ranking[i].record);
	}
	fprintf(stderr, "%s\n", "Passou");
}

void clearRank(rank *r, char *file) {
	criarRankingFile(r, file);
	int tam = getSizeRank(r);
	for (int i = 0; i < tam; i++) {
		free(r[i].name);
	}
	free(r);
}

