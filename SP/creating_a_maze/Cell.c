#include <stdio.h>
#include <stdlib.h>
#include "Cell.h"
#include "Maze.h"

Cell CL_new (Maze mz, int x, int y) {
    Cell new;
    new.x = x;
    new.y = y;
    new.lc = (struct cell*)calloc, sizeof(struct cell);
    for (int i = 0; i < _x*_y; i++)
        new.color[i] = 255;
    if (new.x = 0) new = CL_addLeftWall(new);
    if (new.x = mz.width - 1) new = CL_addRightWall(new);
    if (new.y = 0) new = CL_addUpperWall(new);
    if (new.y = mz.height - 1) new = CL_addDownWall(new);
    return new;
}

/*void CL_draw (Cell cell, FILE *f) {
    fprintf(f, "P2\n");
    fprintf(f, "%d %d\n", _x, _y);
    fprintf(f, "255\n");
    for (int i = 0; i < _x*_y; i++)
        fprintf(f, "%d ", cell.color[i]);
}*/

Cell CL_addUpperWall (Cell cell) {
    for (int i = 0; i < _x*4; i++)
        cell.color[i] = 0;
        return cell;
}

Cell CL_addDownWall (Cell cell) {
    for (int i = _x*_y-2*_y; i < _x*_y; i++)
        cell.color[i] = 0;
        return cell;
}

Cell CL_addLeftWall (Cell cell) {
    for (int i = 0; i < _y; i++) {
        for (int j = 0; j < _x/5; j++) {
            cell.color[i*20+j] = 0;
        }
    }
    return cell;
}

Cell CL_addRightWall (Cell cell) {
    for (int i = 0; i < _y; i++) {
        for (int j = _y*4/5; j < _y; j++) {
            cell.color[i*20+j] = 0;
        }
    }
    return cell;
}
