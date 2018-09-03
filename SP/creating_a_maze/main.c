#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Maze.h"

int main() {
    FILE *f = fopen("maze.ppm", "w");
    FILE *c = fopen("before.ppm", "w");
    // FILE *c = fopen("cell.ppm", "w");

    srand(time(NULL));

    Maze mz = MZ_new(4, 4);
    // Cell cell = CL_new(mz, 0, 0);
    // printf("%d %d\n", mz.width, mz.height);
    // CL_draw(mz.arr[2], c);
    printf("%d %d\n", mz.entrance.x, mz.entrance.y);
    printf("%d %d\n", mz.exit.x, mz.exit.y);
    char been[16];
    for (int i = 0; i < 16; i++) {
        been[i] = 0;
    }
    MZ_draw(mz, c);
    mz = MZ_makePath(mz, mz.entrance, been);


    MZ_draw(mz, f);

    fclose(f);
    fclose(c);
    return 0;
}
