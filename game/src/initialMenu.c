#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include "logger.h"
#include "image.h"
#include "global.h"
//...



int initialMenu(int trying)
{
    
   //posicao do teclado
    int pos=1;
    int posicao_menu=1;
    int temp=0;
    int enter=0;

  
    bool closeDisplay =false;
    logger("Menu inicial.");
    fprintf(stderr, "initialMenu\n" );
    int option;

    // ---------------------------------------------------------------------
    //Fila de eventos
    ALLEGRO_EVENT_QUEUE *filaDeEventos = al_create_event_queue();
    if(!filaDeEventos){
        erro("Falha ao criar evento");                                                                        
    }
                                                                                                                   
    
                                                                                                            
                                                                                                            
   // al_register_event_source(filaDeEventos, al_get_display_event_source(display));
    // ----------------------------------------------------------------------
    //Fonte
    ALLEGRO_FONT *fonteMenu = NULL;
    al_init_font_addon();

     if (!al_init_ttf_addon())
    {
        fprintf(stderr, "falha ao carregar fonte.\n");
        return -1;
    }

    fonteMenu = al_load_font("res/fonts/Digital dream Fat.ttf", 35, 0);
    
     
      if (!al_install_keyboard())
        {
            fprintf(stderr, "Teclado não inicializou.\n");
            return false;
        }
    // ---------------------------------------------------------------------------------------

    //Carregamento do background do Menu
    image backgroundMenu = newImage(al_load_bitmap("res/img/concert.jpg"));
    drawBackground(backgroundMenu);
    // ---------------------------------------------------------------------------------------
    al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 70, ALLEGRO_ALIGN_CENTRE, "1-Iniciar");
    al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 160, ALLEGRO_ALIGN_CENTRE, "2-Tutorial");
    al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 250, ALLEGRO_ALIGN_CENTRE, "3-Ranking");
    al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 340, ALLEGRO_ALIGN_CENTRE, "4-Sair");
    al_flip_display();
   // -----------------------------------------------------------------------------------------
    




while(!closeDisplay)
{
    while(!al_is_event_queue_empty(filaDeEventos))
    {
    ALLEGRO_EVENT jogar;
    al_wait_for_event(filaDeEventos, &jogar);
        if(jogar.type == ALLEGRO_EVENT_KEY_DOWN)
        {
        switch(jogar.keyboard.keycode)
        {
            case ALLEGRO_KEY_UP:
            pos = pos+1;
            if(pos>4)
            {
                pos=4;

            }
            break;

            case ALLEGRO_KEY_DOWN:
            pos= pos-1;

            if(pos<1)
            {
                pos=1;
            }
            break;

            case ALLEGRO_KEY_ENTER:
            pos = 10;
            break;

    
            }
            }
        else if(jogar.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
        closeDisplay = true;
        }

int initialMenu(int trying)  {
	logger("Menu inicial.");
	fprintf(stderr, "initialMenu\n" );
	int option;
	scanf("%d", &option);
	return option;

}




switch(pos)    
    {

        case 1:
        al_draw_text(fonteMenu, al_map_rgb(255, 255, 255),300, 70, ALLEGRO_ALIGN_CENTRE, "1-Iniciar");
        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 160, ALLEGRO_ALIGN_CENTRE, "2-Tutorial");
        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 250, ALLEGRO_ALIGN_CENTRE, "3-Ranking");
        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 340, ALLEGRO_ALIGN_CENTRE, "4-Sair");
        al_flip_display();
        puts("case1");
        break;
        
        
    
        case 2:
        
    
        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 70, ALLEGRO_ALIGN_CENTRE, "1-Iniciar");
        al_draw_text(fonteMenu, al_map_rgb(255, 255, 255),300, 160, ALLEGRO_ALIGN_CENTRE, "2-Tutorial");
        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 250, ALLEGRO_ALIGN_CENTRE, "3-Ranking");
        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 340, ALLEGRO_ALIGN_CENTRE, "4-Sair");
        al_flip_display();
        puts("case2");
        break;


        

        case 3:

        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 70, ALLEGRO_ALIGN_CENTRE, "1-Iniciar");
        al_draw_text(fonteMenu, al_map_rgb(255, 255, 255),300, 160, ALLEGRO_ALIGN_CENTRE, "2-Tutorial");
        al_draw_text(fonteMenu, al_map_rgb(255, 255, 255),300, 250, ALLEGRO_ALIGN_CENTRE, "3-Ranking");
        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 340, ALLEGRO_ALIGN_CENTRE, "4-Sair");
        al_flip_display();
        puts("case3");
        break;

        case 4:

        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 70, ALLEGRO_ALIGN_CENTRE, "1-Iniciar");
        al_draw_text(fonteMenu, al_map_rgb(255, 255, 255),300, 160, ALLEGRO_ALIGN_CENTRE, "2-Tutorial");
        al_draw_text(fonteMenu, al_map_rgb(255, 192, 203),300, 250, ALLEGRO_ALIGN_CENTRE, "3-Ranking");
        al_draw_text(fonteMenu, al_map_rgb(255,255, 255),300, 340, ALLEGRO_ALIGN_CENTRE, "4-Sair");
        al_flip_display();
        puts("case4");
        break;

        
    }


}   



 

    
    scanf("%d", &option);    

    return option;
}




