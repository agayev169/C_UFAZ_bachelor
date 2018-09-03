#include <stdio.h>
#include "Maze.h"
#include "Cell.h"

int main()
{
	int width, height;//Width and height of the maze
	printf("Width of maze: ");scanf("%d", &width);
	printf("Height of maze: ");scanf("%d", &height);
	Maze mz = MZ_new(width, height, MZ_REALHARD);

	Cell entrance = CL_entrance(mz);
	Cell exit = CL_exit(mz);

	int cells = width * height;
	Cell solution[100];
	short been[cells];//The variable in which we have information whether we have been in given cell or not(1 for visited cells and 0 for not visited)
	for (int i = 0; i < cells; ++i)//For loop to initialize all the values of been as 0
		been[i] = 0;
	int steps = 0;
	int max_steps = 0;
	int this_steps;

	// CL_calloc (mz, entrance, exit, &solution, steps, been, width);//Calloc of solution array
	// for (int i = 0; i < cells; ++i)//For loop to initialize all the values of been as 0 since after calloc some cells were visited
	// 	been[i] = 0;
	// CL_findExit (mz, entrance, exit, solution, steps, been, width, &max_steps);//Finding exit and writing all the path into solution
	// CL_setSolution (mz, solution, max_steps);
	// MZ_saveImg(mz, "myMaze.ppm");
	// MZ_free(mz);

	char found = 0;
	//for (int i = 0; i < 100; ++i)
	//{
		for (int j = 0; j < cells; ++j)
		{
			been[j] = 0;
		}
	//	printf("Iteration #%d\n", i);
		CL_findExitRealHard (mz, entrance, exit, solution, steps, been, width, &max_steps, &this_steps);//Finding exit and writing all the path into solution
	//}
	for (int i = 0; i < max_steps; ++i){
		CL_print(solution[i]);
	}
	CL_setSolution (mz, solution, max_steps);
	printf("Saving\n");
	MZ_saveImg(mz, "myRealHardMaze.ppm");
	printf("Done!\n");
	MZ_free(mz);



	return 0;
}
