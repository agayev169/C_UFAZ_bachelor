#include <stdio.h>
#include <stdlib.h>
#include "DistField.h"

DistField DF_new(int Nx, int Ny) {
    DistField df;
    df.arr = (int*)calloc(Nx*Ny, sizeof(int));
    df.width = Nx;
    df.height = Ny;
    for (int i = 0; i < Ny; i++) {
        for (int j = 0; j < Nx; j++)
            df.arr[Nx*i+j] = DF_INFINITY;
    }
    return df;
}

int DF_get(DistField df, int x, int y) {
    return df.arr[df.width*y+x];
}

void DF_set(DistField df, int x, int y, int val) {
    df.arr[df.width*y+x] = val;
}

void DF_show(DistField df, char *label) {
    printf("---------------%s---------------\n", label);
    for (int i = 0; i < df.height; i++) {
        for (int j = 0; j < df.width; j++)
            printf("%d ", DF_get(df, j, i));
        printf("\n");
    }
}

bool DF_propagate(DistField df, Cell c1, Cell c2) {
    if (DF_get(df, c1.x, c1.y) > DF_get(df, c2.x, c2.y) + 1) {
        df.arr[df.width*c2.x+c2.y] = df.arr[df.width*c1.x+c1.y] + 1;
        return TRUE;
    }
    return FALSE;
}

bool DF_propagatableLinkedCell(Maze mz, DistField df, Cell c, Cell *lnkneigh) {
    Cell linked_cells[4];
    int size = CL_linkedCells(mz, c, linked_cells);
    for (int i = 0; i < size; i++) {
        if()
    }
}
