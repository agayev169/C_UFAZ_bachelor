#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    FILE *image = fopen("final.ppm", "r");
    FILE *new = fopen("rand.ppm", "w");
    char format[3];
    fscanf(image, "%s", format);
    int width, height;
    fscanf(image, " %d %d ", &width, &height);
    fprintf(new, "%s\n", format);
    fprintf(new, "%d %d\n", width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(new, "%d ", rand() % 2);
        fprintf(new, "\n");
        }
    }

    return 0;
}
