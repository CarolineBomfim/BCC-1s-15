#include <stdio.h>
#include <stdlib.h>
#include "musicGame.h"
#include "logger.h"

#define TAMANHO_LINHA 4
#define TAMANHO_BLOCO 4

music alocaMusic(int total);

music readFileMusic(char *file) {
	FILE *arquivo_carregado;
	arquivo_carregado = fopen( file, "r");
	char *linha = malloc(TAMANHO_LINHA*sizeof(char));
	int total = 0;
	char att[3];
	int bloco = 0, line = 0;
	music musica;
	if(!arquivo_carregado) {
		erro("Falha ao carregar arquivo com as notas.");
	}

	while(fgets(linha, TAMANHO_LINHA, arquivo_carregado) != NULL) {
		if( linha[0] == '#' ) {
			if (linha[2]) {
				att[0] = linha[2];
				att[1] = linha[3];
				att[2] = linha[4];
				total = atoi(att);
				musica = alocaMusic(total);
			}
		} else {
			// Define a divisão de um bloco
			if(linha[0] == '=') {
				line = 0;
				bloco++;
			} else {
				for (int i = 0; i < TAMANHO_LINHA; ++i) {
					musica.music[bloco][line][i] = linha[i];
				}
				line++;
			}
		}
	}
	free(linha);
	fclose(arquivo_carregado);
	return musica;
}

void freeMusic(music musica){
	for (int i = 0; i < musica.nBlocos; ++i) {
		for (int j = 0; j < TAMANHO_BLOCO; ++j) {
			free(musica.music[i][j]);
		}
		free(musica.music[i]);
	}
	free(musica.music);
}

music alocaMusic(int total) {
	music musica;
	musica.nBlocos = total/TAMANHO_BLOCO;
	musica.music = malloc(musica.nBlocos*sizeof(int **));
	for (int i = 0; i < musica.nBlocos; ++i) {
		musica.music[i] = malloc(TAMANHO_BLOCO*sizeof(int *));
		for(int j = 0; j < TAMANHO_BLOCO; ++j) {
			musica.music[i][j] = malloc(TAMANHO_LINHA*sizeof(int));
		}
	}
	return musica;
}
