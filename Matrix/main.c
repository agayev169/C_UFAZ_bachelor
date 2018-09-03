#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

int main() {
    srand(time(NULL));
    int size = 10;
    Matrix m = newMatrix(size);
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            m.data[i][j] = 1 / (double) (i + j + 1);
        }
    }
    Matrix inv = inverse(m);
    print(m);
    printf("\n");
    print(inv);
    printf("\n");
    print(mult(m, inv));


    return 0;
}