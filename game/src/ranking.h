#ifndef _RAKING_H_
#define _RAKING_H_
typedef struct _rank{
	char *name;
	int record;
}rank;

rank *ordenaRank(rank *ranking);
int getSizeFile(char *arquivo);
int getRecord(char *linha);
char *getName(char *linha);
rank montar_ranking(char *linha);
rank *ler_ranking(char *caminho_arquivo);
void showRanking(rank *ranking);
void clearRank(rank *r, char *file);

#endif
