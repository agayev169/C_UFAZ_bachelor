#include <stdio.h>
#include "Maze.h"
#include "Cell.h"
int main() {
	Maze mz = MZ_new(8,8,MZ_MEDIUM);

	//cell solution[3];
	cell exit = CL_exit(mz);
	cell entrance = CL_entrance(mz);
	// cell unexp[4];
	// int size = unExploredLinkedCells(mz, CL_new(13,0), unexp, CL_new(13, 1));
	// for (int i = 0; i < size; ++i) {
	// 	CL_print(unexp[i]);
	// }
	// int step = 0;
	// CL_findPath(mz, entrance, exit, step, solution);
	// CL_setSolution (mz, 3, solution);

	int step = 0;
	cell solution[64];
	CL_findPathMedium(mz, entrance, exit, step, solution);
	MZ_saveImg(mz,"myFirstMaze.ppm");
	MZ_free(mz);

	return 0;
}
