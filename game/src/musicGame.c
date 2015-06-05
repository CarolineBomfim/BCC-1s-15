#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global.h"
#include "musicGame.h"
#include "logger.h"

music alocaMusic(int totalBlocks) {
	music musica;
	musica.nBlocos = totalBlocks;
	musica.music = malloc(musica.nBlocos*sizeof(char **));
	for (int i = 0; i <= musica.nBlocos; i++) {
		musica.music[i] = malloc(TAMANHO_BLOCO*sizeof(char *));
		for(int j = 0; j <= TAMANHO_BLOCO; j++) {
			musica.music[i][j] = malloc(TAMANHO_LINHA*sizeof(char));
		}
	}
	return musica;
}

music readFileMusic(global_var *global, char *file) {
	FILE *arquivo_carregado;
	arquivo_carregado = fopen( file, "r");

	if(!arquivo_carregado) {
		erro("Falha ao carregar arquivo com as notas.");
	}

	char *linha = malloc(TAMANHO_LINHA*sizeof(char));
	
	int musicSize = 0;
	char *att = malloc(2*TAMANHO_BLOCO*sizeof(char));
	int bloco = 0, line = 0;
	

	fscanf(arquivo_carregado, "%d", &musicSize);

	if(global->gameMode != NORMAL_MODE) {
		printf("Music size = %d\n", musicSize);
	}

	music musica;
	musica = alocaMusic(musicSize);

	int count = 0;
	int _while = musicSize;
	while(count < (musicSize-1)) {

		fscanf(arquivo_carregado, "%s", linha);


		if(linha[0] == '=') {
			bloco++;
			line = 0;
		}
		
		if(linha[0] == '#') {
			count--;
		}

		if(linha[0] != '#' && linha[0] != '='){
			for (int character = 0; character < TAMANHO_LINHA; character++) {
				if(linha[character] == 48 || linha[character] == 49) {
					musica.music[bloco][line][character] = linha[character];
				}
			}

			if(global->gameMode == DEBUG_MODE) {
				printf("\n(%d)\t%s\t %d\t%d\n", count, linha, line, bloco);
				for(int character = 0; character < TAMANHO_LINHA; character++) {
					printf("> %c\t", musica.music[bloco][line][character]);
				}
				printf("\n");
			}
			line++;
		}

		count++;
	}

	free(linha);
	fclose(arquivo_carregado);
	return musica;
}

void freeMusic(music musica){
	for (int i = 0; i <= musica.nBlocos; ++i) {
		for (int j = 0; j <= TAMANHO_BLOCO; ++j) {
			free(musica.music[i][j]);
		}
		free(musica.music[i]);
	}
	free(musica.music);
}
