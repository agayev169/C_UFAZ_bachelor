#include <stdio.h>
#include "Maze.h"
#include "Cell.h"

Cell CL_new (int x, int y) {
	Cell temp = {x, y};
	return temp;
}

void CL_print (Cell cell) {
	printf("%d %d\n", cell.x, cell.y);
}

short CL_same (Cell cell1, Cell cell2) {
	if (cell1.x == cell2.x && cell1.y == cell2.y) return 1;
	else return 0;
}


Cell CL_entrance (Maze mz) {
	Cell temp;
	MZ_entrance(mz, &temp.x, &temp.y);
	return temp;
}

Cell CL_exit (Maze mz) {
	Cell temp;
	MZ_exit(mz, &temp.x, &temp.y);
	return temp;
}

void CL_linkedCells (Maze mz, Cell cell, Cell linked_cells[], int *size) {
	int lc[8];
	*size = MZ_linkedCells(mz, cell.x, cell.y, lc);
	for (int i = 0; i < *size; ++i) {
		linked_cells[i].x = lc[2*i];
		linked_cells[i].y = lc[2*i+1];
	}
}

void CL_setSolution (Maze mz, Cell cell[], int nb_cells) {
	int solution[nb_cells*2];
	for (int i = 0; i < nb_cells; ++i)
	{
		solution[2*i] = cell[i].x;
		solution[2*i+1] = cell[i].y;
	}
	MZ_setSolution(mz, solution, nb_cells);
}

int CL_findExit (Maze mz, Cell cell, Cell exit, Cell *solution, int steps, short been[], int width, int *max_steps) {
	// static int count = 0;
	// count++;
	// if (count > 20)
	// {
	// 	return 0;
	// }
	printf("%d %d %d %d\n", cell.x, cell.y, been[width * cell.y + cell.x], steps);
	if (been[width * cell.y + cell.x] == 1) {
		return 0;
	}
	been[width * cell.y + cell.x] = 1;
	if (CL_same(cell, exit) == 1) {
		//solution = (Cell *) calloc (steps+1, sizeof(Cell));
		solution[steps].x = cell.x;
		solution[steps].y = cell.y;
		*max_steps = steps + 1;
		return 1;
	}

	Cell lc[4] = {0};
	int lc_size;
	CL_linkedCells(mz, cell, lc, &lc_size);

	for (int i = 0; i < lc_size; ++i) {
		if (CL_findExit(mz, lc[i], exit, solution, steps+1, been, width, max_steps) == 1) {
			printf("%d %d step = %d\n", cell.x, cell.y, steps);
			solution[steps].x = cell.x;
			solution[steps].y = cell.y;
			return 1;
		}
	}
	return 0;
}