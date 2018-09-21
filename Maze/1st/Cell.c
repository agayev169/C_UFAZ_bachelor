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
	return 0;
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

int CL_linkedCells (Maze mz, Cell cell, Cell linked_cells[]) {
	int lc[8];
	int size = MZ_linkedCells(mz, cell.x, cell.y, lc);
	for (int i = 0; i < size; ++i) {
		linked_cells[i].x = lc[2*i];
		linked_cells[i].y = lc[2*i+1];
	}
	return size;
}

void CL_setSolution (Maze mz, Cell path[], int nb_cells) {
	int solution[nb_cells*2];
	for (int i = 0; i < nb_cells; ++i)
	{
		solution[2*i] = path[i].x;
		solution[2*i+1] = path[i].y;
	}
	MZ_setSolution(mz, solution, nb_cells);
	printf("Solution was set\n");
}

int CL_calloc(Maze mz, Cell current_cell, Cell exit, Cell **solution, int steps, short been[], int width) {
	if (been[width * current_cell.y + current_cell.x] == 1)//If we have been in the current cell the function will return 0
		return 0;
	been[width * current_cell.y + current_cell.x] = 1;//Else we initialize that we are in the current cell
	if (CL_same(current_cell, exit) == 1) {//If we are in the exit cell we calloc solution and return 1 which means that function call was successful
		*solution = (Cell *) calloc (steps+1, sizeof(Cell));
		return 1;
	}

	Cell lc[4] = {0};
	int lc_size = CL_linkedCells(mz, current_cell, lc);

	for (int i = 0; i < lc_size; ++i) {
		if (CL_calloc(mz, lc[i], exit, solution, steps+1, been, width) == 1)//If we found an exit once we just exit the function
			return 1;
	}
	return 0;//If there was any problem in the previous statements this one will exit the function
}

int CL_findExit (Maze mz, Cell current_cell, Cell exit, Cell solution[], int steps, short been[], int width, int *max_steps) {
	if (been[width * current_cell.y + current_cell.x] == 1)//If we have been in the current cell the function will return 0
		return 0;
	been[width * current_cell.y + current_cell.x] = 1;//Else we initialize that we are in the current cell
	if (CL_same(current_cell, exit) == 1) {//If we are in the exit cell we initialize steps element of solution as current cell and return 1 which means that function call was successful
		(solution[steps]).x = current_cell.x;
		(solution[steps]).y = current_cell.y;
		*max_steps = steps + 1;
		return 1;
	}

	Cell lc[4] = {0};
	int lc_size = CL_linkedCells(mz, current_cell, lc);

	for (int i = 0; i < lc_size; ++i) {
		if (CL_findExit(mz, lc[i], exit, solution, steps+1, been, width, max_steps) == 1) {//If we found an exit once we initialize steps element of solution as current cell and exit the function
			(solution[steps]).x = current_cell.x;
			(solution[steps]).y = current_cell.y;
			return 1;
		}
	}
	return 0;//If there was any problem in the previous statements this one will exit the function
}

Cell CL_next (Maze maze, short been[], Cell linked_cells[], int lc_size, int width) {
	int temp = been[width * linked_cells[0].y + linked_cells[0].x];
	int n = 0;
	int static counter = 0;
	counter++;
	for (int i = 1; i < lc_size; ++i) {
		if (been[width * linked_cells[i].y + linked_cells[i].x] < temp) {
			temp = been[width * linked_cells[i].y + linked_cells[i].x];
			n = i;
		} else if (been[width * linked_cells[i].y + linked_cells[i].x] == temp && rand()%5 == 0) {
			temp = been[width * linked_cells[i].y + linked_cells[i].x];
			n = i;
		}
	}
	if (counter == 9999) {
		CL_print(linked_cells[n]);		
	}
	return linked_cells[n];
}

/*void CL_findExitRealHard (Maze mz, Cell current_cell, Cell previous, Cell exit, Cell solution[], int steps, short been[], int width, int *max_steps, char *found, int *this_steps) {
	// CL_print(current_cell);
	if (CL_same(current_cell, previous))
		return;
	been[width * current_cell.y + current_cell.x]++;
	if (CL_same(current_cell, exit)) {
		*this_steps = steps + 1;
		if (steps < *max_steps || *max_steps == 0) {
			printf("%d steps; %d max_steps\n", *this_steps, *max_steps);
			printf ("I'm in exit: "); CL_print(current_cell);
			(solution[steps]).x = current_cell.x;
			(solution[steps]).y = current_cell.y;
			*max_steps = steps + 1;
			*found = 1;
		}
			// printf("Found exit\n");
		return;
	}
		Cell lc[4];
	int lc_size = CL_linkedCells(mz, current_cell, lc);
	for (int j = 0; j < lc_size; ++j) {
		Cell next = CL_next(mz, been, lc, lc_size, width);
		if (CL_same(next, previous) && lc_size == 1) return;
		while (CL_same(next, previous)) next = CL_next(mz, been, lc, lc_size, width);
		//CL_print(current_cell);
		for (int i = 0; i < lc_size; ++i) {
			printf("linked_cells[%d] = ", i);
			CL_print(lc[i]);
			printf("Previous = "); CL_print(previous);
		}
		CL_findExitRealHard(mz, next, current_cell, exit, solution, steps+1, been, width, max_steps, found, this_steps);
	}
	if (*this_steps == *max_steps || *max_steps == 0 && *found == 1) {
		printf("Setting a solution\n");
		// for (int i = 0; i < *max_steps; ++i) {
		// 	CL_print(solution[i]);
		// }
		printf("Exit is ");
		CL_print(exit);
		printf("Before setting solution\n");
		// CL_print(current_cell);
		(solution[steps]).x = current_cell.x;
		(solution[steps]).y = current_cell.y;
		printf("After setting solution\n");
	}
}*/

//I didn't find this function useful so I commented it but although I wrote it to not skip it
// int unExploredLinkedCells (Maze mz, Cell cell, Cell unExploredLinkedCells[], Cell explored) {
// 	Cell linked_cells[4];
// 	int nb_neighbours = CL_linkedCells(mz, cell, linked_cells);
// 	int counter = 0;
// 	while (counter < nb_neighbours - 1) {
// 		if (CL_same(explored, linked_cells[counter]) == 0) {
// 			unExploredLinkedCells[counter].x = linked_cells[counter].x;
// 			unExploredLinkedCells[counter].y = linked_cells[counter].y;
// 		} else {
// 			for (int i = counter+1; i < nb_neighbours; ++i) {
// 				unExploredLinkedCells[counter].x = linked_cells[i].x;
// 				unExploredLinkedCells[counter].y = linked_cells[i].y;
// 				counter++;
// 			}
// 		}
// 		counter++;
// 	}
// 	return nb_neighbours - 1;
// }

int CL_findExitRealHard (Maze mz, Cell current_cell, Cell exit, Cell solution[], int steps, short been[], int width, int *max_steps, int *this_steps) {
	CL_print(current_cell);
	if (been[width * current_cell.y + current_cell.x] == 1)//If we have been in the current cell the function will return 0
		return 0;
	been[width * current_cell.y + current_cell.x] = 1;//Else we initialize that we are in the current cell
	if (CL_same(current_cell, exit) == 1) {//If we are in the exit cell we initialize steps element of solution as current cell and return 1 which means that function call was successful
		(solution[steps]).x = current_cell.x;
		(solution[steps]).y = current_cell.y;
		*max_steps = steps + 1;
		return 1;
	}

	Cell lc[4] = {0};
	int lc_size = CL_linkedCells(mz, current_cell, lc);

	for (int i = 0; i < lc_size; ++i) {
		if (CL_findExitRealHard(mz, lc[i], exit, solution, steps+1, been, width, max_steps, this_steps) == 1 && (*this_steps == *max_steps || *max_steps == 0)) {//If we found an exit once we initialize steps element of solution as current cell and exit the function
			printf("initializing an array\n");
			(solution[steps]).x = current_cell.x;
			(solution[steps]).y = current_cell.y;
			printf("Array is initialized\n");
			return 1;
		}
	}
	return 0;//If there was any problem in the previous statements this one will exit the function
}