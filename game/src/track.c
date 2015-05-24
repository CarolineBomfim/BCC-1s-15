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

void conversionHSV(unsigned char *rgb, int *hsv) {
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
	hsv[SATURATION] = (int)s*100;
	hsv[LIGHTNESS] = (int)v;
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
	int largura = global->configure->largura;
	int ***hsv = malloc(altura*sizeof(int**));
	
	camera_atualiza(global->camera1);
	
	for(int i = altura/2; i < altura; i++) {
		hsv[i] = malloc(largura*sizeof(int*));
		for(int j = largura/2; j < largura; j++) {
			hsv[i][j] = malloc(3*sizeof(int));
			conversionHSV(global->camera1->quadro[i][j], hsv[i][j]);
			
			for(int k = 0; k < global->configure->num_obj; k++) {
				// Aprimorar valores para o ambiente adequado
				printf("(%d) %d %d %d %d %d %d\n", k,
							attr[k].h_min < hsv[i][j][HUE],
							hsv[i][j][HUE] < attr[k].h_max,
							attr[k].s_min < hsv[i][j][SATURATION],
							hsv[i][j][SATURATION] < attr[k].s_max,
							attr[k].v_min < hsv[i][j][LIGHTNESS], 
							hsv[i][j][LIGHTNESS] < attr[k].v_max );
				if(
				   attr[k].h_min < hsv[i][j][HUE]
				   && hsv[i][j][HUE] < attr[k].h_max
				   && attr[k].s_min < hsv[i][j][SATURATION]
				   && hsv[i][j][SATURATION] < attr[k].s_max
				   && attr[k].v_min < hsv[i][j][LIGHTNESS] 
				   && hsv[i][j][LIGHTNESS] < attr[k].v_max
				  ) {
					if(i < altura/2) {
						// Pegando a centroide de cada um dos pontos
						marks[k][POSITION_X] += j;
						marks[k][POSITION_Y] += i;
						complemento++;
					}
				}
			}
			free(hsv[i][j]);
		}
		free(hsv[i]);
	}
	free(hsv);
	for (int i = 0; i < global->configure->num_obj; ++i) {
		positions[i][POSITION_X] = complemento > 0 ? marks[i][POSITION_X]/complemento : 0;
		positions[i][POSITION_Y] = complemento > 0 ? marks[i][POSITION_Y]/complemento : 0;
		free(marks[i]);
	}
	free(marks);
}
