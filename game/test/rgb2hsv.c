#include <stdio.h>
#include <stdlib.h>

// Valores de rgb
#define RED   0
#define GREEN 1
#define BLUE  2

// Valores de hsv
#define HUE        0
#define SATURATION 1
#define LIGHTNESS  2

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

	s = max == 0 ? 0 : (d/max);
	printf("%f\n", max);
	printf("%f\n", d);
	printf("%f\n", s);

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

int main(int argc, char **argv) {
	unsigned char *rgb = malloc(3*sizeof(unsigned char));
	unsigned char *hsv = malloc(3*sizeof(unsigned char));
	rgb[RED] = atoi(argv[1]);
	rgb[GREEN] = atoi(argv[2]);
	rgb[BLUE] = atoi(argv[3]);
	conversionHSV(rgb, hsv);
	printf("h=%d s=%d v=%d\n", hsv[HUE], hsv[SATURATION], hsv[LIGHTNESS]);
	free(hsv);
	free(rgb);
	return 0;
}