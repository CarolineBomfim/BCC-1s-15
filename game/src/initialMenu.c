#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "logger.h"
#include "global.h"
#include "image.h"

int initialMenu(int trying, global_var *global)  {
	logger("Menu inicial.");
	
	if(!al_set_system_mouse_cursor(global->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) {
		erro("Falha ao habilitar o cursor padrão do sistema.");
	}

	// Prepara fila de eventos para receber eventos do mouse.
	al_register_event_source(global->event_queue, al_get_mouse_event_source());

	int largura = global->configure->largura;
	// Dividindo a altura da tela em 4 blocos, a largura será a largura da tela inteira.
	int altura = global->configure->altura/4;

	int mouse_y = 0;
	int mouse_x = 0;
	// background do menu
	image menuBackground = newImage(al_load_bitmap("res/img/background_menu.png"));

	// Imagens de seleção
	image selection = newImage(al_load_bitmap("res/img/selectIcon.png"));
	image start_game = newImage(al_create_bitmap(altura, largura));
	image ranking = newImage(al_create_bitmap(altura, largura));
	image exit_game = newImage(al_create_bitmap(altura, largura));

	setPositiony(selection, altura);
	setPositiony(start_game, altura);
	setPositiony(ranking, altura*2);
	setPositiony(exit_game, altura*3);

	while(true) {
		while(!al_is_event_queue_empty(global->event_queue)) {

			ALLEGRO_EVENT event;
			al_wait_for_event(global->event_queue, &event);

			// Eventos de movimento
			if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
				mouse_y = event.mouse.y;
				mouse_x = event.mouse.x;
					// Start game
				if(mouse_y > getPositiony(start_game) && mouse_y < getPositiony(ranking)) {
					setPositiony(selection, altura*1);
					// Ranking
				} else if(mouse_y > getPositiony(ranking) && mouse_y < getPositiony(exit_game)) {
					setPositiony(selection, altura*2);
					// Exit
				} else if(mouse_y > getPositiony(exit_game)) {
					setPositiony(selection, altura*3);
				}
			// Caso o evento seja um click
			} else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
					//Start game
				if(mouse_y > getPositiony(start_game) && mouse_y < getPositiony(ranking)) {
					return 0;
					// Ranking
				} else if(mouse_y > getPositiony(ranking) && mouse_y < getPositiony(exit_game)) {
					return 1;
					//Exit
				} else if(mouse_y > getPositiony(exit_game)) {
					return 2;
				}
			}
		}
		drawBackground(menuBackground);
		draw(selection);
		al_flip_display();
	}
}
