#ifndef _GRID_H_
#define _GRID_H_

#include <stdio.h>
#include <stdlib.h>

struct g 
{
	int width, height;
	int *array;
};

typedef struct g Grid;

Grid G_new (int width, int height);
int G_get(Grid g, int i, int j);
void G_set(Grid g, int i, int j, int value);

#endif
