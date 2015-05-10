#include <stdio.h>
#include <allegro5/allegro.h>
#include "camera.h"
#include "logger.h"
#include "global.h"

int initialMenu(int trying, global_var *global)  {
	logger("Menu inicial.");
	int option = 0;
	if(!al_set_system_mouse_cursor(global->display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)) {
		erro("Falha ao habilitar o cursor padrão do sistema.");
	}

	if(!al_register_event_resource(global->event_queue, al_get_mouse_event_source())) {
		erro("Falha ao registrar eventos do mouse na fila de eventos");
	}

	while(TRUE) {
		al_flip_display();

		// Caso a event_queue esteja vazio, verificar eventos do mouse no while
		while(!al_is_event_queue_empty(global->event_queue)) {
			ALLEGRO_EVENT event;
			al_wait_for_event(global->event_queue, event);

			// Eventos de movimento
			if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
				fprintf(stderr, "X = %d Y = %d\n", event.mouse.x, event.mouse.y);
				// Caso o evento seja um click
			} else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				fprintf(stderr, "Click\n" );
			}
		}
	}

	return option;
}
