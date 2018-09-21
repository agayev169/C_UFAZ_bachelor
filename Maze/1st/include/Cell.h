typedef struct 
{
	int x;
	int y;
} Cell;
//A new struct Cell whose components are x and y coordinates of a cell

Cell CL_new (int x, int y);
//Input is two integer variables: x and y coordinates of cell
//Output is a cell with coordinates x and y 

void CL_print (Cell cell);
//Input is a cell
//Prints x and y coordinates of a given cell

short CL_same (Cell cell1, Cell cell2);
//Input is two Cell variables: cell1 and cell2
//Output is 1 if x and y components of both Cells are equal else output is 0

Cell CL_entrance (Maze mz);
//Input is Maze
//Output is a Cell with coordinates of entrance of the Maze "mz"

Cell CL_exit (Maze mz);
//Input is Maze
//Output is a Cell with coordinates of exit of the Maze "mz"

int CL_linkedCells (Maze mz, Cell cell, Cell linked_cells[]);
//Input is Maze, Cell, array of Cells linked_cells which will be filled agter calling of the function
//After calling of the function linked_cells[] will be filled with neighbour Cells of a given Cell
//Output is a number of neighbours of a given Cell

void CL_setSolution (Maze mz, Cell path[], int nb_cells);
//Input is Maze, array of Cells which is a path from 1 point to another and integer variable which is a size of the array
//After calling of the function it draws the ppm image of maze with the solution path[] 

//int unExploredLinkedCells (Maze mz, Cell cell, Cell unExploredLinkedCells[], Cell explored);
//Input is Maze, Cell, Cell variable explored in which we have a cell which is explored at the moment and
//array of Cells unExploredCells which will be filled by the cells which we haven't explored yet
//Output is an integer which represents a number of unexplored linked cells
//I commented this function because I didn't find it useful in the code that I've written. I've found faster algorithm with usage of less memory

int CL_calloc(Maze mz, Cell current_cell, Cell exit, Cell **solution, int steps, short been[], int width);
//The aim of this function is to save the memory of the computer on which the code will be executed 
//Input is Maze, Cell in which we are at the moment, exit Cell, pointer to pointer to Cell which will be allocated to save the memory, 
//integer variable steps which will be the size of the array, array of shorts in which we have information whether we have been at the current cell
//and width which is a width of the maze
//Output is a 1 if function call was successful and 0 else
//After calling of the function it dynamically allocates the array of Cells solution which will be used after as a path from entrance to exit

int CL_findExit (Maze mz, Cell current_cell, Cell exit, Cell solution[], int steps, short been[], int width, int *max_steps);
//The aim of this function is to find the path from the entrance cell to the exit cell
//Input is Maze, Cell in which we are at the moment, exit Cell, array of Cells which will be filled with our path, 
//integer variable steps which will be the index of the current cell in the array, array of shorts in which we have information whether we have been at the current cell,
//integer variable width which is a width of the maze and the pointer to integer max_steps which will be a size of solution array(we will need it later on)
//Output is a 1 if function call was successful and 0 else
//After calling of the function it fills array of Cells solution with cells that will form the path from entrance to exit

// void CL_findExitRealHard (Maze mz, Cell current_cell, Cell previous, Cell exit, Cell solution[], int steps, short been[], int width, int *max_steps, char *found, int *this_steps);

int CL_findExitRealHard (Maze mz, Cell current_cell, Cell exit, Cell solution[], int steps, short been[], int width, int *max_steps, int *this_steps);

Cell CL_next (Maze maze, short been[], Cell linked_cells[], int lc_size, int width);