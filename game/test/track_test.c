#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "src/camera.h"
#include "src/global.h"
#include "src/track.h"
#include "src/logger.h"

int main() {
  al_init();

  if(!al_init_image_addon()) {
    erro("Falha ao carregar biblioteca de images.");
  }

  if(!al_init_primitives_addon()) {
    erro("Falha ao carregar biblioteca de formas.");
  }
  printf("Arquivo de configuração\n");
  config *configuracao        = ler_arquivo_configuracao(ARQUIVO_CONFIG);
  global_var *global          = malloc(sizeof(global_var));

  printf("Criando janela\n");
  global->display             = al_create_display((2*configuracao->largura), configuracao->altura);
  if(!global->display) {
    erro("Falha ao criar tela");
  }
  printf("criando camera\n");
  global->camera1             = camera_inicializa(configuracao->cam);
  camera_atualiza(global->camera1);

  //Associar arquivo de configuração a variavel global
  global->configure = configuracao;

  printf("Criando fila de eventos\n");  
  global->event_queue         = al_create_event_queue();
  
  if(!global->event_queue) {
    erro("Falha ao criar fila de eventos");
  }
  

  printf("Criando cores\n");
  ALLEGRO_COLOR white         = al_map_rgb(255,255,255);
  ALLEGRO_COLOR black         = al_map_rgb(0,0,0);
  ALLEGRO_COLOR red           = al_map_rgb(237,23,97);
  ALLEGRO_COLOR green         = al_map_rgb(10,212,153);
  ALLEGRO_COLOR blue          = al_map_rgb(55,47,223);
  ALLEGRO_COLOR pink          = al_map_rgb(228,65,220);
  ALLEGRO_COLOR color         = al_map_rgb(0,0,0);

  printf("Preparando buffer\n");    
  ALLEGRO_BITMAP *buffer      = al_get_backbuffer(global->display);
  printf("Preparando prevew\n");    
  ALLEGRO_BITMAP *preview     = al_create_sub_bitmap(buffer, 0, 0, global->configure->largura, global->configure->altura);
  ALLEGRO_BITMAP *preview2    = al_create_sub_bitmap(buffer, global->configure->largura, 0, global->configure->largura, global->configure->altura);


  printf("Preparando posicoes\n");
  printf("%d\n", global->configure->num_obj);
  int **positions = malloc(global->configure->num_obj*sizeof(int *));
  
  for(int i = 0; i < global->configure->num_obj; i++){
    positions[i] = malloc(2*sizeof(int));
  }

  // Faz a checagem para verificar se o fundo é igual.
  global->snapshot = getSnapshot(global);
  
  // Para evitar alocar e desalocar uma matriz o todo novo ciclo, utilizar uma unica matriz 
  // e altarar os valores a cada novo ciclo
  global->hsv = getSnapshot(global);
  
  if(!global->snapshot || !global->hsv) {
    erro("Erro ao copiar o primeiro frame.");
  }
  printf("while\n");
  while(1) {
    camera_atualiza(global->camera1);
    camera_copia(global->camera1, global->camera1->quadro, preview);
    track(global, positions);

    // Posição real do objeto detectado
    for (int k = 0; k < global->configure->num_obj; k++) {
      if(k == 0) {
        color = red;
      } else if(k ==1 ) {
        color = green;
      } else if(k == 2) {
        color = blue;
      } else if(k == 3) {
        color = pink;
      } else if (k == 4) {
        color = white;
      } else {
        color = black;
      }
      al_draw_circle(positions[k][0], positions[k][1], 30.0, color, 2.0);
    }
    
    camera_copia(global->camera1, global->camera1->quadro, preview2);
    al_flip_display();
  }

  al_destroy_display(global->display);
  camera_finaliza(global->camera1);
  for(int i = 0; i < global->configure->num_obj; i++){
    free(positions[i]);
  }
  free(positions);
  freeSnapshot(global, global->hsv);
  freeSnapshot(global, global->snapshot);

  free(global);
  exit(EXIT_SUCCESS);
  return 0;
}
