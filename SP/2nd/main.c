#include <stdio.h>
#include "Maze.h" // Maze.h is needed for operating on a maze.
#include "Solution.h" // Solution.h is needed for solving the maze.

int main() // This function is the main function.
{
	Maze mz = MZ_new(20, 20, MZ_HARD); // A maze is generated.
	MZ_saveImg(mz, "myMaze.ppm"); // A picture of the maze is created and saved.

	int width, height; // Integers for containing the width and the height of the maze are created.
	MZ_size(mz, &width, &height); // The width and the height of the maze is initailized.
	Cell* solution=(Cell*)calloc(width*height, sizeof(Cell)); // The block of memory is allocated for an array "solution" to contain all the possible combinations of the cells which constitute the solution path.
	int nb_path=S_build(mz, solution, width * height); // The "solution" array is initialized and the length of "solution" is obtained.
	CL_setSolution(mz, solution, nb_path); // The solution is set accordingly to the "solution" array.

	MZ_saveImg(mz, "mySolution.ppm"); // A picture of a solution is created and saved.
	MZ_free(mz); // The memory allocated for the maze "mz" is freed.
	return 0; // The program is finished.
}
