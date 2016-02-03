#include <cstdlib>
#include <cmath>
#include <cassert>
#include "Util.h"

int Util::randomInt(int a, int b) {
        return a + rand() % (b - a + 1);
}

double Util::randomDouble(double a, double b) {
        return a + (b - a) * rand() / (double) RAND_MAX;
}

bool Util::randomBool(double p) {
        return rand() / (double) RAND_MAX < p;
}

char Util::doubleToChar(double x) {
	assert(x <= 1.0);
	int i = x * 256;
	if (i >= 256) i = 255;
	return (char) i;
}

void Util::HSVtoRGB(double * r, double * g, double * b, double h, double s, double v) {
	int i;
	double f, p, q, t;

	if (s == 0) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}
	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );
	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}

