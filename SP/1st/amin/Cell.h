#include <stdio.h>
#include "Maze.h"
typedef struct Cell {
	int x;
	int y;
}cell;
//Using typedef to write faster "struct cell", as "cell".

cell CL_new(int x, int y);
// This function creates for us 2 variables, which means  2 dimensions.
// Input 2 values , output cell, which takes this values.

void CL_print(cell kletka);
//It will print us 2 values of struct kletka, which means "x" and "y"
int CL_check(cell kletka,cell kletka1);
// It will check that if our 2 cells equal or not.
// If they are equal, function returns 1, else => returning 0.

cell CL_entrance(Maze mz);
// This function will create for us an entrance cell, from which we will begin with coordinates of the Maze"mz".
cell CL_exit (Maze mz);
//This function will create for us an exit(last)cell, in which we will end.
int CL_linkedCells (Maze mz, cell kletka, cell linked_cells[]);
//This function


void CL_setSolution (Maze mz, int nb_cells,cell kletka[]);

int CL_findPath (Maze mz, cell current_kletka, cell exit, int step, cell solution[]);

int unExploredLinkedCells (Maze mz,cell c, cell unExploredLinkedCells[], cell explored);

int CL_findPathMedium (Maze mz, cell current_cell, cell exit, int step, cell solution[]);