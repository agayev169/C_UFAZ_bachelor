#ifndef __CELL_H__
#define __CELL_H__

#include <stdio.h>
#include "Maze.h"

typedef struct cell {
    int x, y;
    struct cell *lc;//linked cells
    unsigned char color[400];
} Cell;

Cell CL_new (struct maze mz, int x, int y);

// void CL_draw (Cell cell, FILE *f);

Cell CL_addUpperWall (Cell cell);

Cell CL_addDownWall (Cell cell);

Cell CL_addLeftWall (Cell cell);

Cell CL_addRightWall (Cell cell);

#endif
