#include <stdio.h>
#include "logger.h"

int initialMenu(int trying) {
	logger("Menu inicial.");
	fprintf(stderr, "initialMenu\n" );
	int option;
	scanf("%d", &option);
	return option;
}