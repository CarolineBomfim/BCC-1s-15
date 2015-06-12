#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "logger.h"
#include "global.h"
#include "image.h"
#include "cursor.h"
#include "target.h"
#include "track.h"
#include "musicGame.h"

bool successShot(int **positions, target target) {
  
  if(cursorInArea(positions) && targetInArea(target)) {
    for(int i = 0; i < 2; i++ ) {
      if(positions[i][POSITION_X] > getPositionTargetx(target)) {
        if(positions[i][POSITION_X] < (getPositionTargetx(target) + TARGET_WIDTH)) {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

int startGame(global_var *global) {
  
  bool unespectedStop = FALSE;
  
  logger("Iniciar jogo");
  
  camera_atualiza(global->camera1);

  // Faz a checagem para verificar se o fundo é igual.
  global->snapshot = getSnapshot(global);
  
  // Para evitar alocar e desalocar uma matriz o todo novo ciclo, utilizar uma unica matriz 
  // e altarar os valores a cada novo ciclo
  global->hsv = getSnapshot(global);
  
  if(!global->snapshot || !global->hsv) {
    erro("Erro ao copiar o primeiro frame.");
  }

  // 0.5 segundo
  ALLEGRO_TIMER *timer      = al_create_timer(0.5);

  // 1 segund
  ALLEGRO_TIMER *timerOfEvent = al_create_timer(1.0);

  // Fila de eventos local
  ALLEGRO_EVENT_QUEUE *timerEventQueue = al_create_event_queue();

  // Prepara filas de eventos 
  al_register_event_source(global->event_queue, al_get_timer_event_source(timer));
  al_register_event_source(global->event_queue, al_get_display_event_source(global->display));
  al_register_event_source(timerEventQueue, al_get_timer_event_source(timerOfEvent));

  int **positions = malloc(global->configure->num_obj*sizeof(int *));
  for (int i = 0; i < global->configure->num_obj; ++i) {
    positions[i] = malloc(2*sizeof(int));
  }

  ALLEGRO_FONT *font         = al_load_font("res/font/aardc.ttf", 36, 0);
  if(!font) {
    erro("Erro ao carregar fonte.");
  }

  image background           = newImage(al_load_bitmap("res/img/background_image.png"));
  target alvoAzul            = newTarget(al_load_bitmap("res/img/alvo_azul.png"));
  target alvoAzul2           = newTarget(al_load_bitmap("res/img/alvo_azul.png"));
  target alvoRosa            = newTarget(al_load_bitmap("res/img/alvo_rosa.png"));
  target alvoRosa2           = newTarget(al_load_bitmap("res/img/alvo_rosa.png"));
  target alvoVerde           = newTarget(al_load_bitmap("res/img/alvo_verde.png"));
  target alvoVerde2            = newTarget(al_load_bitmap("res/img/alvo_verde.png"));
  target alvoVermelho        = newTarget(al_load_bitmap("res/img/alvo_vermelho.png"));
  target alvoVermelho2       = newTarget(al_load_bitmap("res/img/alvo_vermelho.png"));
  target error1              = newTarget(al_load_bitmap("res/img/errorImage.png"));
  target error2              = newTarget(al_load_bitmap("res/img/errorImage.png"));
  target error3              = newTarget(al_load_bitmap("res/img/errorImage.png"));
  target error4              = newTarget(al_load_bitmap("res/img/errorImage.png"));
  ALLEGRO_BITMAP *buffer     = al_get_backbuffer(global->display);
  ALLEGRO_BITMAP *preview    = al_create_sub_bitmap(buffer, 0, 0, global->configure->largura, global->configure->altura);

  // Colors
  ALLEGRO_COLOR white       = al_map_rgb(255,255,255);
  ALLEGRO_COLOR black       = al_map_rgb(0,0,0);
  ALLEGRO_COLOR red         = al_map_rgb(237,23,97);
  ALLEGRO_COLOR green       = al_map_rgb(10,212,153);
  ALLEGRO_COLOR blue        = al_map_rgb(55,47,223);
  ALLEGRO_COLOR pink        = al_map_rgb(228,65,220);

  // Musica
  ALLEGRO_SAMPLE_INSTANCE *sample;
  ALLEGRO_SAMPLE *sample_data = al_load_sample(global->music);
  // Carregando musica e as notas
  music music_notes           = readFileMusic(global, global->music_notes);
  if(!music_notes.nBlocos) {
    erro("Erro ao carregar arquivo de notas.");
  }

  if(!sample_data) {
    erro("Erro ao carregar musica.");
  }

  sample = al_create_sample_instance(NULL);
  if (!al_set_sample(sample, sample_data)) {
    erro("Erro ao associar a musica a instancia.");
  }

  // Organizando posições do alvo, o diametro de cada alvo é de 95px
  setPositionTarget(alvoAzul     , INICIO_AREA_ALVO_X                 , 0);
  setPositionTarget(alvoAzul2    , INICIO_AREA_ALVO_X                 , 0);
  setPositionTarget(alvoRosa     , INICIO_AREA_ALVO_X + TARGET_WIDTH  , 0);
  setPositionTarget(alvoRosa2    , INICIO_AREA_ALVO_X + TARGET_WIDTH  , 0);
  setPositionTarget(alvoVermelho , INICIO_AREA_ALVO_X + 2*TARGET_WIDTH, 0);
  setPositionTarget(alvoVermelho2, INICIO_AREA_ALVO_X + 2*TARGET_WIDTH, 0);
  setPositionTarget(alvoVerde    , INICIO_AREA_ALVO_X + 3*TARGET_WIDTH, 0);
  setPositionTarget(alvoVerde2   , INICIO_AREA_ALVO_X + 3*TARGET_WIDTH, 0);

  // Definindo propriedades das imagens de erro
  setPositionTarget(error1, INICIO_AREA_ALVO_X                 , INICIO_AREA_ALVO_Y);
  setPositionTarget(error2, INICIO_AREA_ALVO_X + TARGET_WIDTH  , INICIO_AREA_ALVO_Y);
  setPositionTarget(error3, INICIO_AREA_ALVO_X + 2*TARGET_WIDTH, INICIO_AREA_ALVO_Y);
  setPositionTarget(error4, INICIO_AREA_ALVO_X + 3*TARGET_WIDTH, INICIO_AREA_ALVO_Y);

  //Carregando cursores
  cursor left = newCursor(al_load_bitmap("res/img/cursor_left.png"));
  cursor right = newCursor(al_load_bitmap("res/img/cursor_right.png")); 
  
  // Os cursores devem ficar a baixo da linha que define a ação
  setCursorPosition(right, global->configure->largura/2, global->configure->altura - 120);
  setCursorPosition(left, global->configure->largura/2, global->configure->altura - 120);

  // Modo de jogo para registro
  if (global->gameMode == TESTING_MODE) {
    logger("Jogo iniciado em modo de teste. Todas as atividades serão registradas.");
  } else if(global->gameMode == DEBUG_MODE) {
    logger("Jogo iniciado em modo de debug. Todas as atividades serão registradas.");
  } else {
    logger("Jogo iniciado em modo padrão.");
  }

  // Iniciando audio
  al_set_sample_instance_playmode(sample, ALLEGRO_PLAYMODE_LOOP);

  // Inicia o timer
  al_start_timer(timer);
  al_start_timer(timerOfEvent);

  int timerCounting = 0;
  int block         = 0;
  int line          = 0;
  int count         = 0;
  int cascateaux    = 0;
  bool newBlock     = TRUE;
  int trackaux      = 0;
  int compareaux    = 3;
  logger("Inicando a musica");
  while(TRUE){

    ALLEGRO_EVENT event, blockEvent;

    al_wait_for_event(timerEventQueue, &blockEvent);
    al_wait_for_event(global->event_queue, &event);

    // Executa o rastreamento e retorna a posição dos objetos rastrados
    
    track(global, positions);
    setCursorsPosition(global, left, right, positions);
    

    if(event.type == ALLEGRO_EVENT_TIMER) {
      timerCounting++;
      // Limpa os erros
      hideTarget(error1);
      hideTarget(error2);
      hideTarget(error3);
      hideTarget(error4);
    }

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      unespectedStop = TRUE;
      break;
    }

    // Encerra o laço até quando a música chega ao fim, solução temporaria
    // 600 = tempoDaMusica*2
    if(timerCounting == 600) {
      break;
    }

    if(timerCounting == 16) {
      al_play_sample(sample_data, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    }

    // Notas a serem impressas na tela
    if(trackaux == compareaux) {
      if(blockEvent.type == ALLEGRO_EVENT_TIMER ){
        if(newBlock) {
          newBlock = FALSE;

          if(global->gameMode == DEBUG_MODE) {
            printf("(%d) (%d) (%s)\n", block, line, music_notes.music[block][line]);
          }

          for(int i = 0; i < TAMANHO_LINHA; i++) {
            if(i == 0 && music_notes.music[block][line][0] == '1') {
              if(isShow(alvoAzul)) {
                showTarget(alvoAzul2);
              } else {
                showTarget(alvoAzul);
              }
            }

            if(i == 1 && music_notes.music[block][line][1] == '1') {
              if(isShow(alvoRosa)) {
                showTarget(alvoRosa2);
              } else {
                showTarget(alvoRosa);
              }
            }

            if(i == 2 && music_notes.music[block][line][2] == '1') {
              if(isShow(alvoVermelho)) {
                showTarget(alvoVermelho2);
              } else {
                showTarget(alvoVermelho);
              }
            }

            if(i == 3 && music_notes.music[block][line][3] == '1') {
              if(isShow(alvoVerde)) {
                showTarget(alvoVerde2);
              } else {
                showTarget(alvoVerde);
              }
            }
          }

          // Passa o bloco  
          line++;
          if(line == 4) {
            block++;
            line = 0;
          }
        }

        if(cascateaux == global->configure->speedPass) {
          newBlock = TRUE;
          cascateaux = 0 ;
        }
      }
    }
    // gameMode representa como o jogo será executado
    // gameMode=0 será executado de forma padrão, apenas com registros de rotina.
    // gameMode=1 será executada como teste, então background que não será mostrada.
    // gameMode=2 será executado como debug, mostrara mais informações no terminal
    // como a valor que estiver dentro do range rastreado, não será.

    // Imrpimindo elementos na tela
    if(global->gameMode == NORMAL_MODE) {
      drawBackground(background);
    } else {
      camera_copia(global->camera1, global->camera1->quadro, preview);

      // Define a linha do bloco de ação
      al_draw_line((double)INICIO_AREA_ALVO_X, 0,(double)INICIO_AREA_ALVO_X, global->configure->altura,black, 2);
      al_draw_line((double)FIM_AREA_ALVO_X,    0,(double)FIM_AREA_ALVO_X   , global->configure->altura,black, 2);
      
      // Trilho dos alvos
      al_draw_line((double)(INICIO_AREA_ALVO_X + TARGET_WIDTH)  , 0,(double)(INICIO_AREA_ALVO_X +   TARGET_WIDTH),global->configure->altura,black, 1);      
      al_draw_line((double)(INICIO_AREA_ALVO_X + 2*TARGET_WIDTH), 0,(double)(INICIO_AREA_ALVO_X + 2*TARGET_WIDTH),global->configure->altura,black, 1);
      al_draw_line((double)(INICIO_AREA_ALVO_X + 3*TARGET_WIDTH), 0,(double)(INICIO_AREA_ALVO_X + 3*TARGET_WIDTH),global->configure->altura,black, 1);
    }

    if(trackaux == compareaux){
      // Area relevante da detecção
      if(timerCounting > 5) {

        if ( targetsInArea(alvoAzul, alvoRosa, alvoVermelho, alvoVerde)
            || targetsInArea(alvoAzul2, alvoRosa2, alvoVermelho2, alvoVerde2)) {
          
          if(cursorInArea(positions)) {
            if(successShot(positions, alvoAzul)) {
              al_draw_filled_circle((double)INICIO_AREA_ALVO_X, (double)(INICIO_AREA_ALVO_Y+(TARGET_WIDTH/2)), (double)(TARGET_WIDTH/2), blue);
              if(global->gameMode == DEBUG_MODE) {
                printf("success shot blue\n");
              }
              resetTargetPositionForce(alvoAzul);
            } else if(successShot(positions, alvoAzul2)) {
              al_draw_filled_circle((double)INICIO_AREA_ALVO_X, (double)(INICIO_AREA_ALVO_Y+(TARGET_WIDTH/2)), (double)(TARGET_WIDTH/2), blue);
              if(global->gameMode == DEBUG_MODE) {
                printf("success shot blue\n");
              }
              resetTargetPositionForce(alvoAzul2);
            }

            if(successShot(positions, alvoRosa)) {
              al_draw_filled_circle((double)((INICIO_AREA_ALVO_X+(TARGET_WIDTH/2)) + TARGET_WIDTH), (double)(INICIO_AREA_ALVO_Y+(TARGET_WIDTH/2)), (double)(TARGET_WIDTH/2), pink);
              if(global->gameMode == DEBUG_MODE) {
                printf("success shot pink\n");
              }
              resetTargetPositionForce(alvoRosa);
            } else if(successShot(positions, alvoRosa2)) {
              al_draw_filled_circle((double)((INICIO_AREA_ALVO_X+(TARGET_WIDTH/2)) + TARGET_WIDTH), (double)(INICIO_AREA_ALVO_Y+(TARGET_WIDTH/2)), (double)(TARGET_WIDTH/2), pink);
              if(global->gameMode == DEBUG_MODE) {
                printf("success shot pink\n");
              }
              resetTargetPositionForce(alvoRosa2);
            } 

            if(successShot(positions, alvoVermelho)){
              al_draw_filled_circle((double)((INICIO_AREA_ALVO_X+(TARGET_WIDTH/2)) + 2*TARGET_WIDTH), (double)(INICIO_AREA_ALVO_Y+(TARGET_WIDTH/2)), (double)(TARGET_WIDTH/2), red);
              if(global->gameMode == DEBUG_MODE) {
                printf("success shot red\n");
              }
              resetTargetPositionForce(alvoVermelho);
            } else if(successShot(positions, alvoVermelho2)) {
              al_draw_filled_circle((double)((INICIO_AREA_ALVO_X+(TARGET_WIDTH/2)) + 2*TARGET_WIDTH), (double)(INICIO_AREA_ALVO_Y+(TARGET_WIDTH/2)), (double)(TARGET_WIDTH/2), red);
              if(global->gameMode == DEBUG_MODE) {
                printf("success shot red\n");
              }
              resetTargetPositionForce(alvoVermelho2);
            } 

            if(successShot(positions, alvoVerde)) {
              al_draw_filled_circle((double)((INICIO_AREA_ALVO_X+(TARGET_WIDTH/2)) + 3*TARGET_WIDTH), (double)(INICIO_AREA_ALVO_Y+(TARGET_WIDTH/2)), (double)(TARGET_WIDTH/2), green);
              if(global->gameMode == DEBUG_MODE) {
                printf("success shot green\n");
              }
              resetTargetPositionForce(alvoVerde);
            } else if(successShot(positions, alvoVerde2)) {
              al_draw_filled_circle((double)((INICIO_AREA_ALVO_X+(TARGET_WIDTH/2)) + 3*TARGET_WIDTH), (double)(INICIO_AREA_ALVO_Y+(TARGET_WIDTH/2)), (double)(TARGET_WIDTH/2), green);
              if(global->gameMode == DEBUG_MODE) {
                printf("success shot green\n");
              }
              resetTargetPositionForce(alvoVerde2);
            } 
          } else {
            if(targetInArea(alvoAzul)) {
              showTarget(error1);
              resetTargetPositionForce(alvoAzul);
              if(global->gameMode == DEBUG_MODE) {
                printf("show error error1\n");
              }
            } else if(targetInArea(alvoAzul2)) {
              showTarget(error1);
              resetTargetPositionForce(alvoAzul2);
              if(global->gameMode == DEBUG_MODE) {
                printf("show error error1\n");
              }
            }
            if(targetInArea(alvoRosa)) {
              showTarget(error2);
              resetTargetPositionForce(alvoRosa);
              if(global->gameMode == DEBUG_MODE) {
                printf("show error error2\n");
              }
            } else if(targetInArea(alvoRosa2)) {
              showTarget(error2);
              resetTargetPositionForce(alvoRosa2);
              if(global->gameMode == DEBUG_MODE) {
                printf("show error error2\n");
              }
            }
            if(targetInArea(alvoVermelho)) {
              showTarget(error3);
              resetTargetPositionForce(alvoVermelho);
              if(global->gameMode == DEBUG_MODE) {
                printf("show error error3\n");
              }
            } else if(targetInArea(alvoVermelho2)) {
              showTarget(error3);
              resetTargetPositionForce(alvoVermelho2);
              if(global->gameMode == DEBUG_MODE) {
                printf("show error error3\n");
              }
            }
            if(targetInArea(alvoVerde)) {
              showTarget(error4);
              resetTargetPositionForce(alvoVerde);
              if(global->gameMode == DEBUG_MODE) {
                printf("show error error4\n");
              }
            } else if(targetInArea(alvoVerde2)) {
              showTarget(error4);
              resetTargetPositionForce(alvoVerde2);
              if(global->gameMode == DEBUG_MODE) {
                printf("show error error4\n");
              }
            }
          }
        }
      }
    }

    // Efeito cascata dos alvos
    cascateTargets(global, alvoAzul, alvoRosa, alvoVermelho, alvoVerde);
    cascateTargets(global, alvoAzul2, alvoRosa2, alvoVermelho2, alvoVerde2);

    // Desenha na tela tudo que é padrão para todos os modos de jogo

    // Posição real do objeto detectado
    for (int k = 0; k < global->configure->num_obj; k++) {
      if(k == CURSOR_ESQUERDO) {
        al_draw_circle(positions[CURSOR_ESQUERDO][POSITION_X], positions[CURSOR_ESQUERDO][POSITION_Y], 30.0, blue, 2.0);
      } else if(k == CURSOR_DIREITO) {
        al_draw_circle(positions[CURSOR_DIREITO][POSITION_X], positions[CURSOR_DIREITO][POSITION_Y], 30.0, red, 2.0);
      }
    }

    if(global->gameMode == NORMAL_MODE) {
      al_draw_line((double)INICIO_AREA_ALVO_X, (double)INICIO_AREA_ALVO_Y,(double)FIM_AREA_ALVO_X,(double)INICIO_AREA_ALVO_Y, black, 2);
      al_draw_line((double)INICIO_AREA_ALVO_X, (double)FIM_AREA_ALVO_Y   ,(double)FIM_AREA_ALVO_X,(double)FIM_AREA_ALVO_Y   , black, 2);
    } else {
      al_draw_line((double)INICIO_AREA_ALVO_X, (double)INICIO_AREA_ALVO_Y,(double)FIM_AREA_ALVO_X,(double)INICIO_AREA_ALVO_Y, white, 2);
      al_draw_line((double)INICIO_AREA_ALVO_X, (double)FIM_AREA_ALVO_Y   ,(double)FIM_AREA_ALVO_X,(double)FIM_AREA_ALVO_Y   , white, 2);
    }

    // Informações da musica
    al_draw_textf(font, green, (global->camera1->largura/2) + 100, 30, ALLEGRO_ALIGN_LEFT, "%s", global->music_name );
    al_draw_textf(font, green, (global->camera1->largura/2) + 180, 70, ALLEGRO_ALIGN_LEFT, "%s", global->music_band );

    drawTargets(alvoAzul, alvoRosa, alvoVermelho, alvoVerde);
    drawTargets(alvoAzul2, alvoRosa2, alvoVermelho2, alvoVerde2);
    drawTargets(error1, error2, error3, error4);

    // Cursor para mostrar em  qual alvo está o objeto
    // drawCursor(left);
    // drawCursor(right);

    if(trackaux == compareaux) 
      trackaux = 0;
    count++;
    cascateaux++;
    trackaux++;
    al_flip_display();
  }

  freeMusic(music_notes);
  al_destroy_sample(sample_data);
  for (int i = 0; i < global->configure->num_obj; ++i) {
    free(positions[i]);
  }
  free(positions);
  
  freeSnapshot(global, global->snapshot);
  freeSnapshot(global, global->hsv);
  
  clearImage(background);
  clearTarget(alvoAzul);
  clearTarget(alvoAzul2);
  clearTarget(alvoRosa);
  clearTarget(alvoRosa2);
  clearTarget(alvoVerde);
  clearTarget(alvoVerde2);
  clearTarget(alvoVermelho);
  clearTarget(alvoVermelho2);
  clearTarget(error1);
  clearTarget(error2);
  clearTarget(error3);
  clearTarget(error4);
  clearCursor(left);
  clearCursor(right);

  if(unespectedStop) {
    return (-1);
  }
  return 1;
}
