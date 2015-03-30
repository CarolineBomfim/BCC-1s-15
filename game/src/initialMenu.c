#include <stdio.h>
#include "logger.h"

///ALLEGRO_BITMAP *btJogar = NULL;
///ALLEGRO_BITMAP *btTutorial = NULL;
///ALLEGRO_BITMAP *btSair = NULL;



int initialMenu(int trying) 
{
	logger("Menu inicial.");
	fprintf(stderr, "initialMenu\n" );
	int option;
	scanf("%d", &option);
	return option;
}



     
