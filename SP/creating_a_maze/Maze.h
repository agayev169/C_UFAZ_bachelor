#ifndef __MAZE_H__
#define __MAZE_H__

#include <stdio.h>

#define TRUE 1
#define FALSE 0

//--------------------Cell-------------------------------------

typedef struct cell {
    int x, y;
    struct cell *lc;//linked cells
    char lc_number;
    unsigned char color[400];
} Cell;

//--------------------Maze-------------------------------------

typedef struct maze {
    struct cell *arr;
    int width, height;
    struct cell entrance, exit;
} Maze;

//--------------------Stack-------------------------------------

typedef struct stack  {
    Cell *cells;
    int number_cells;
} Stack;

//--------------------Maze-------------------------------------

Maze MZ_new (int width, int height);

void MZ_draw (Maze maze, FILE *f);

Maze MZ_makePath (Maze mz, Cell cell, char been[]);

//--------------------Cell-------------------------------------

Cell CL_new (int x, int y);

void CL_draw (Cell cell, FILE *f);

Cell CL_drawEntrance (Cell cell);

Cell CL_drawExit (Cell cell);

Cell CL_addUpperWall (Cell cell);

Cell CL_deleteUpperWall (Cell cell);

Cell CL_addDownWall (Cell cell);

Cell CL_deleteDownWall (Cell cell);

Cell CL_addLeftWall (Cell cell);

Cell CL_deleteLeftWall (Cell cell);

Cell CL_addRightWall (Cell cell);

Cell CL_deleteRightWall (Cell cell);

char CL_same (Cell cell1, Cell cell2);

//--------------------Stack-------------------------------------

Stack ST_new (int size);

#endif
