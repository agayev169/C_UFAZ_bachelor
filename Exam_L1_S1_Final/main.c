//Done!
#include <stdio.h>
#include "DistField.h"

int main() {
    int width = 5, height = 10;
    DistField df = DF_new(width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            DF_set(df, j, i, width*i+j);
        }
    }
    DF_show(df, "DistField");

    return 0;
}
//Done!
