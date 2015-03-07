#include "include.h"

void registro_evento(char *msg) {
	FILE *ArquivoLog;
	time_t agora = time(NULL);
	struct tm *t = localtime(&agora);
	int dia = t->tm_mday;
	int mes = t->tm_mon + 1;
	int ano = t->tm_year + 1900;
	int hora = t->tm_hour;
	int minuto = t->tm_min;
	int segundo = t->tm_sec;

	ArquivoLog = fopen("LogInterno.log", "a");
		
		fprintf(ArquivoLog, "%d:%d:%d %d/%d/%d - \"%s\"\n", hora, minuto, segundo, dia, mes, ano, msg);
		fprintf(ArquivoLog, "--\n");

	fclose(ArquivoLog);
}

void erro(char *msg){
	printf("%s\n", msg);
	registro_evento(msg);
	exit(EXIT_FAILURE);
}
