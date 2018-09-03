#include "ExplorationMarker.h"

// From now on ExplorationMarker will be referred to as marker in the comments.

ExplorationMarker EM_new(int nc, int nl)
{
	ExplorationMarker ans=(ExplorationMarker)malloc(sizeof(StructExplorationMarker)); // A block of memory is allocated for the answer marker.
	ans->_nb_columns=nc; // The number of columns of the answer marker is set.
	ans->_nb_lines=nl; // The number of lines of the answer marker is set.
	ans->_array=(boolean*)calloc(nc*nl, sizeof(boolean)); // A block of memory for the array containing markers for each cell is allocated.
	return ans; // The answer marker is returned.
}

void EM_free(ExplorationMarker em)
{
	free(em->_array); // The block of memory containing the array of the marker "em" is freed.
	free(em); // The block of memory containing the marker "em" is freed.
}

void EM_check(ExplorationMarker em, char *label)
{
	printf("%s is a label:\n", label); // The "label" is printed. (I don't know why would anyone ever need this line of code.)
	for(int i=0; i<em->_nb_lines; i++) // For each line:
	{
		if(em->_nb_columns) // (Can be ignored.)
			printf("%c", em->_array[i*(em->_nb_columns)+0]); // (Can be ignored.)
		for(int j=1; j<em->_nb_columns; j++) // For each column:
			printf(" %c", em->_array[i*(em->_nb_columns)+j]); // The element of the marker "em" is printed.
		printf("\n"); // Switching to the next line.
	}
}

void EM_clear(ExplorationMarker em)
{
	for(int i=0; i<em->_nb_lines; i++) // For each line:
		for(int j=1; j<em->_nb_columns; j++) // For each column:
			em->_array[i*(em->_nb_columns)+j]=0; // The element of the marker "em" is set to 0 (a.k.a. "false").
}

boolean EM_isMarked(ExplorationMarker em, Cell c)
{
	return em->_array[c.y*(em->_nb_columns)+c.x]; // Value of the element of the marker "em" corresponding to the cell "c" is returned.
}

void EM_mark(ExplorationMarker em, Cell c)
{
	em->_array[c.y*(em->_nb_columns)+c.x]=1; // The element of the marker "em" correponding to the cell "c" is set to 1 (a.k.a. "true").
}
