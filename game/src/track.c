#include <stdio.h>
#include <stdlib.h>
#include "global.h"

double caculateMax(double a, double b, double c) {
	if(a >= b) {
		if(b >= c) {
			return a;
		} else {
			if(a > c) {
				return a;
			} else {
				return c;
			}
		}
	} else {
		if(a > c) {
			return b;
		} else {
			if(b > c) {
				return b;
			} else {
				return c;
			}
		}
	}
}

double caculateMim(double a, double b, double c) {
	if(a <= b) {
		if(a <= c) {
			return a;
		} else {
			return c;
		}
	} else {
		if(b <= c) {
			return b;
		} else {
			return c;
		}
	}
}

void conversionHSV(unsigned char *rgb, unsigned char *hsv) {
	double r = (rgb[RED]*100)/255;
	double g = (rgb[GREEN]*100)/255;
	double b = (rgb[BLUE]*100)/255;

	double h= 0.0, s= 0.0, v= 0.0;
	double max = caculateMax(r, g, b);
	double min = caculateMim(r, g, b);

	// d = delta
	double d = max - min;

	v = max;

	s = max == 0 ? 0 : d/max;

	if(d == 0) {
		h = d;
	} else if(max == g) {
		h = 60 * (((b-r)/d)+2);
	} else if(max == b) {
		h = 60 * (((r-g)/d)+4);
	} else if(max == r) {
		h = 60 * ((int)((g-b)/d)%6);
	}

	hsv[HUE] = (int)h;
	hsv[SATURATION] = (int)(s*100);
	hsv[LIGHTNESS] = (int)v;
}

bool aproximateImage(unsigned char *a, unsigned char *b) {
	bool ret = TRUE;
	if(a[RED] != b[RED])
		ret = FALSE;
	else if(a[GREEN] != b[GREEN])
		ret = FALSE;
	else if(a[BLUE] != b[BLUE])
		ret = FALSE;
	return ret;
}
void track(global_var *global, int **positions) {
	atributos *attr = global->configure->atributos;
	int complemento = 0;
	// Marcações 
	int **marks = malloc(global->configure->num_obj*sizeof(int *));
	for (int i = 0; i < global->configure->num_obj; ++i) {
		marks[i] = malloc(2*sizeof(int));
		marks[i][0] = 0;
		marks[i][1] = 0;
	}
	int altura = global->configure->altura;
	int largura = global->configure->largura - 100;

	camera_atualiza(global->camera1);
	// Pega a parte inferior da imagem
	for(int i = INICIO_Y; i < FIM_Y; i++) {
		for(int j = INICIO_X; j < FIM_X; j++) {
			if (!aproximateImage(global->snapshot[i][j], global->camera1->quadro[i][j])) {
				conversionHSV(global->camera1->quadro[i][j], global->hsv[i][j]);
				for(int k = 0; k < global->configure->num_obj; k++) {
					// Aprimorar valores para o ambiente
					if(global->gameMode == NORMAL_MODE || global->gameMode == TESTING_MODE) {
							// Pegando a centroide de cada um dos pontos
						if(attr[k].h_min <= global->hsv[i][j][HUE]
						   && global->hsv[i][j][HUE] <= attr[k].h_max
						   && attr[k].s_min <= global->hsv[i][j][SATURATION]
						   && global->hsv[i][j][SATURATION] <= attr[k].s_max
						   && attr[k].v_min <= global->hsv[i][j][LIGHTNESS] 
						   && global->hsv[i][j][LIGHTNESS] <= attr[k].v_max ) {
	   						marks[k][POSITION_X] += j;
	   						marks[k][POSITION_Y] += i;
	   						complemento++;
	   					}
					} else {
						if (global->gameMode == DEBUG_MODE) {
							if(i == altura/2 && j == largura/2)
								printf("%d\t%d\t%d\n",global->hsv[i][j][HUE], global->hsv[i][j][SATURATION], global->hsv[i][j][LIGHTNESS]);

							if(attr[k].h_min <= global->hsv[i][j][HUE]
								 && attr[k].s_min <= global->hsv[i][j][SATURATION]
								 && attr[k].v_min <= global->hsv[i][j][LIGHTNESS]
								 && global->hsv[i][j][HUE] <= attr[k].h_max
								 && global->hsv[i][j][SATURATION] <= attr[k].s_max
								 && global->hsv[i][j][LIGHTNESS] <= attr[k].v_max
								) {
								printf("(%d)\t%d\t%d\t%d\t<\t%d\t%d\t%d\t<\t%d\t%d\t%d\n", 
								       k+1, attr[k].h_min, attr[k].s_min, attr[k].v_min, 
								       global->hsv[i][j][HUE], global->hsv[i][j][SATURATION], global->hsv[i][j][LIGHTNESS],
								       attr[k].h_max, attr[k].s_max, attr[k].v_max);
								marks[k][POSITION_X] += j;
								marks[k][POSITION_Y] += i;
								complemento++;
							}
						}
					}
				}
				global->hsv[i][j][HUE] = 0;
				global->hsv[i][j][SATURATION] = 0;
				global->hsv[i][j][LIGHTNESS] = 0;
			} else {
				// Para visualizar o que está sendo detectado
				global->camera1->quadro[i][j][RED] = 0;
				global->camera1->quadro[i][j][GREEN] = 0;
				global->camera1->quadro[i][j][BLUE] = 0;
			}
		}
	}
	for (int i = 0; i < global->configure->num_obj; ++i) {
		positions[i][POSITION_X] = complemento > 0 ? marks[i][POSITION_X]/complemento : 0;
		positions[i][POSITION_Y] = complemento > 0 ? marks[i][POSITION_Y]/complemento : 0;
		free(marks[i]);
	}
	free(marks);
}

unsigned char ***getSnapshot(global_var *global) {
	int altura = global->configure->altura;
	int largura = global->configure->largura;
	unsigned char ***snapshot = malloc(altura*sizeof(unsigned char **));
	for (int i = 0; i < altura; i++) {
		snapshot[i] = malloc(largura*sizeof(unsigned char *));
		for (int j = 0; j < largura; j++) {
			snapshot[i][j] = malloc(3*sizeof(unsigned char));
			for(int k = 0; k < 3; k++) {
				snapshot[i][j][k] = global->camera1->quadro[i][j][k];
			}
		}
	}
	return snapshot;
}

void freeSnapshot(global_var *global, unsigned char ***snapshot) {
	int altura = global->configure->altura;
	int largura = global->configure->largura;
	for (int i = 0; i < altura; i++) {
		for (int j = 0; j < largura; j++) {
			free(snapshot[i][j]);
		}
		free(snapshot[i]);
	}
	free(snapshot);
}
