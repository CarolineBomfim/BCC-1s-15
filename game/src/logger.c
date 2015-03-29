#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "logger.h" 
void logger(char *msg) {
	FILE *ArquivoLog;
	time_t agora = time(NULL);
	struct tm *t = localtime(&agora);
	int dia = t->tm_mday;
	int mes = t->tm_mon + 1;
	int ano = t->tm_year + 1900;
	int hora = t->tm_hour;
	int minuto = t->tm_min;
	int segundo = t->tm_sec;

	ArquivoLog = fopen("game.log", "a");
		
		fprintf(ArquivoLog, "%d:%d:%d %d/%d/%d - \"%s\"\n", hora, minuto, segundo, dia, mes, ano, msg);
		fprintf(ArquivoLog, "--\n");

	fclose(ArquivoLog);
}

void erro(char *msg){
	printf("%s\n", msg);
	logger(msg);
	exit(EXIT_FAILURE);
}
