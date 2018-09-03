#include "Solution.h"

int S_unexploredLinkedNeighbors(Maze mz, ExplorationMarker em, Cell c, Cell *ue_linked_cell)
{
	Cell linked_cells[4]; // An array to store all the linked cells of cell "c" is created.
	int nb_links=CL_linkedCells(mz, c, linked_cells); // The array of linked cells is initialized and the number of linked cells is obtained.
	for(int i=0; i<nb_links; i++) // For each linked cell:
	{
		if(!EM_isMarked(em, linked_cells[i])) // If the current considered cell is unmarked:
		{
			*ue_linked_cell=linked_cells[i]; // "ue_linked_cell" is given the value of the current considered cell.
			return 1; // 1 is returned to signalize the existence of an unmarked linked cell.
		}
	}
	return 0; // As default 0 is returned if no unmarked cells were found.
}

void S_trackBackUntilFree(Maze mz, Stack s, ExplorationMarker em)
{
	Cell ue_linked_cell, c; // Two cells are created. One of them will be used as a dummy, the other to store the top cell in stack "s".
	ST_top(s, &c); // Cell "c" is given the value of the top element of the stack "s".
	while(!S_unexploredLinkedNeighbors(mz, em, c, &ue_linked_cell)) // While there are no unexplored linked cells for the top element of the stack "s":
	{
		s=ST_pop(s); // Pop the last element of stack "s" out.
		ST_top(s, &c); // Set the cell "c" to the top element of the stack "s".
	}
}

int S_advanceUntilBlockedOrFound(Maze mz, Stack s, ExplorationMarker em, Cell c, int is_random)
{
	Cell ue_linked_cell; // A cell is created to store an unexplored linked cell.
	while(!CL_isTheSame(c, CL_exit(mz))) // While the top element of the stack is not the same as the exit cell:
	{
		EM_mark(em, c); // Mark the cell corresponding to the top of the stack.
		if(!S_unexploredLinkedNeighbors(mz, em, c, &ue_linked_cell)) // If the top of the stack is a dead-end(if it has no unexplored linked cells):
			return 0; // 0 is returned to signalize a dead-end.
		s=ST_push(s, ue_linked_cell); // An unexplored linked cell is pushed into the stack "s" to be considered in the next iteration.
		ST_top(s, &c); // The cell "c" is given the value of the top element of the stack "s".
	}
	return 1; // As default 1 is returned to signalize that the exit was found.
}

int S_build(Maze mz, Cell *solution, int is_random)
{
	Cell c; // A cell is created to be considered as the top of a possible stack during each iteration.
	int width, height, size; // Integers to contain the width, the height of the maze and the maximal size of a possible stack are created.
	MZ_size(mz, &width, &height); // The width and the height of the maze are obtained.

	ExplorationMarker em=EM_new(width, height); // An exploration marker to contain "width" columns and "height" lines is created.
	EM_clear(em); // The exploration marker is initialized/cleared.
	Stack s=ST_new(width*height); // A stack is created to be able to store "width"*"height" cells.

	s=ST_push(s, CL_entrance(mz)); // The entrance of the maze is pushed into the stack "s" as first cell of the solution path.
	ST_top(s, &c); // Cell "c" is given the value of the top element of the stack (it is given the value of the entrance of the maze).
	while(!S_advanceUntilBlockedOrFound(mz, s, em, c, is_random)) // While the exit is not found after advances:
	{
		S_trackBackUntilFree(mz, s, em); // The cells are tracked back until an unexplored linked cell is found.
		ST_top(s, &c); //  Cell "c" is given the value of the top of the stack.
	}
	ST_export(s, solution); // The elements of the stack containing the solution path are exported to the "solution" array.

	size=ST_size(s); // The size of the "solution" array is stored in "size".
	ST_free(s); // The stack "s" is freed.
	EM_free(em); // The exploration marker is freed.
	return size; // The size of the "solution" is returned.
}
