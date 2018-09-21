#include <stdio.h>
#include "Maze.h"
#include "Cell.h"
#include "time.h"

int main()
{
	long int ini_time = time(NULL);
	int width = 1000, height = 1000;
	Maze mz = MZ_new(width, height, MZ_HARD);

	Cell entrance = CL_entrance(mz);
	Cell exit = CL_exit(mz);

	// Cell solution[1];
	// for (int i = 0; i < 13; ++i)
	// 	solution[i].x = solution[i].y = -1;
	// short been[16] = {0};
	// short a = CL_findWay (mz, entrance, 0, exit, solution, been);
	// CL_setSolution (mz, solution, 13);

	int cells = width * height;
	Cell solution[cells];
	short been[cells];
	for (int i = 0; i < cells; ++i)
		been[i] = 0;
	int steps = 0;
	int max_steps;
	int temp = CL_findExit (mz, entrance, exit, solution, steps, been, width, &max_steps);
	CL_setSolution (mz, solution, max_steps);
	// for (int i = 0; i < 13; ++i)
	// {
	// 	printf("%d %d\n", solution[i].x, solution[i].y);
	// }
	// printf("%d %d\n", solution[0].x, solution[0].y);

	printf("%ld\n", time(NULL)-ini_time);
	MZ_saveImg(mz, "myMaze.ppm");
	MZ_free(mz);

	return 0;
}