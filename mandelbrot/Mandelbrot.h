/*====================================================*\
  Vendredi 8 novembre 2013
  Arash HABIBI
  Mandelbrot.h
\*====================================================*/

#ifndef _MANDELBROT_H_
#define _MANDELBROT_H_

#include <stdio.h>
#include <stdlib.h>
#include "Complex.h"

typedef struct
{
	int _width, _height;
	scalar _zoom_val;
	Complex _zoom;
	Complex _offset;
	Complex _zmin, _zmax;
	int _iteration_max;
	int _threshold;
} Mandelbrot;

Mandelbrot *MB_new(int width, int height);

void MB_check(Mandelbrot *mb, char *message);

int MB_compute(Mandelbrot *mb, int x, int y);

void MB_focusPoint (Mandelbrot *mb, int x, int y);
void MB_zoomInit   (Mandelbrot *mb);
void MB_zoom       (Mandelbrot *mb, scalar zoom_coef);
void MB_move       (Mandelbrot *mb, int x, int y);


#endif
