typedef struct 
{
	int x;
	int y;
} Cell;

Cell CL_new (int x, int y);
void CL_print (Cell cell);
short CL_same (Cell cell1, Cell cell2);
Cell CL_entrance (Maze mz);
Cell CL_exit (Maze mz);
void CL_linkedCells (Maze mz, Cell cell, Cell linked_cells[], int *size);
void CL_setSolution (Maze mz, Cell cell[], int nb_cells);
int CL_findExit (Maze mz, Cell cell, Cell exit, Cell *solution, int steps, short been[], int width, int *max_steps);