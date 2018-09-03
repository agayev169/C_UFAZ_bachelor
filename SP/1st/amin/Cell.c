#include <stdio.h>
#include "Cell.h"
#include "Maze.h"

cell CL_new(int x, int y){
	cell kletka={x,y};
	return kletka;
}

void CL_print(cell kletka){
	printf("kletka.x = %d,kletka.y = %d\n",kletka.x,kletka.y);
}

int CL_check(cell kletka, cell kletka1){
	if(kletka.x==kletka1.x && kletka.y==kletka1.y)
		return 1;
	if(kletka.x!=kletka1.x || kletka.y!=kletka1.y)
		return 0;
}
cell CL_entrance (Maze mz) {
	cell kletka;
	MZ_entrance(mz, &kletka.x, &kletka.y);
	return kletka;
}
cell CL_exit (Maze mz) {
	cell kletka;
	MZ_exit(mz, &kletka.x, &kletka.y);
	return kletka;

}
int CL_linkedCells (Maze mz, cell kletka, cell linked_cells[]) {
	int linked_c[8];
	int size = MZ_linkedCells(mz, kletka.x, kletka.y, linked_c);
	for (int i=0; i<size;i++){
		linked_cells[i].x=linked_c[i*2];
		linked_cells[i].y=linked_c[i*2+1];
	}
	return size;
}
void CL_setSolution (Maze mz, int nb_cells, cell kletka[]){

	int solution[nb_cells*2];
	int i;
	for (i=0; i<nb_cells; i++){
		solution[i*2]=kletka[i].x;
		solution[i*2+1]=kletka[i].y;
	}
	MZ_setSolution(mz, solution, nb_cells);
}

int CL_findPath (Maze mz, cell current_kletka, cell exit, int step, cell solution[]) {
	cell linked_cells[4];
	int nb_neighbours = CL_linkedCells(mz, current_kletka, linked_cells);
	if (step == 2 && CL_check(current_kletka, exit) == 1) {
		solution[step].x = current_kletka.x;
		solution[step].y = current_kletka.y;
		return 1;}
	else if (step == 2) 
		return 0; 
	for (int i = 0; i < nb_neighbours; i++) {
		if (CL_findPath(mz, linked_cells[i], exit, step+1, solution) == 1) {
			solution[step].x = current_kletka.x;
			solution[step].y = current_kletka.y;
			return 1;
		}
	}
	return 0;
}

int unExploredLinkedCells (Maze mz,cell c, cell unExploredLinkedCells[], cell explored) {
	cell linked_cells[4];
	int nb_neighbours = CL_linkedCells(mz, c, linked_cells);
	int counter = 0;
	while (counter < nb_neighbours - 1) {
		if (CL_check(explored, linked_cells[counter]) == 0) {
			unExploredLinkedCells[counter].x = linked_cells[counter].x;
			unExploredLinkedCells[counter].y = linked_cells[counter].y;
		} else {
			for (int i = counter+1; i < nb_neighbours; ++i) {
				unExploredLinkedCells[counter].x = linked_cells[i].x;
				unExploredLinkedCells[counter].y = linked_cells[i].y;
				counter++;
			}
		}
		counter++;
	}
	return nb_neighbours - 1;
}

int CL_findPathMedium (Maze mz, cell current_cell, cell exit, int step, cell solution[]) {
	if (CL_check(exit, current_cell) == 1){
		solution[step].x = current_cell.x;
		solution[step].y = current_cell.y;
		return 1;
	}
	cell lc[4];
	int nb_lc = CL_linkedCells(mz, current_cell, lc);
	while (nb_lc >= 0) {
		if (CL_findPathMedium(mz, lc[0], exit, step+1, solution)==1) {
			solution[step].x = current_cell.x;
			solution[step].y = current_cell.y;
			return 1;
		}
		nb_lc = unExploredLinkedCells(mz, current_cell, lc, lc[0]);
		nb_lc--;
	}
	return 0;
}