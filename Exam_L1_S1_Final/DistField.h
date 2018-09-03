//Done!
#ifndef _DISTFIELD_H_
#define _DISTFIELD_H_


#include "Cell.h"
#include "Maze.h"

#define DF_INFINITY 1000000
#define TRUE 1
#define FALSE 0

typedef unsigned char bool;

typedef struct {
    int *arr;
    int width;
    int height;
}DistField;//1D

DistField DF_new(int Nx, int Ny);
int DF_get(DistField df, int x, int y);
void DF_set(DistField df, int x, int y, int val);
void DF_show(DistField df, char *label);
bool DF_propagate(DistField df, Cell c1, Cell c2);
bool DF_propagatableLinkedCell(Maze mz, DistField df, Cell c, Cell *lnkneigh);

#endif
//Done!
