#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {

    srand(time(NULL));

    FILE *final = fopen("final.ppm", "r");
    FILE *first = fopen("rand.ppm", "r");
    FILE *new = fopen("second.ppm", "w");

    char format[3];
    fscanf(final, "%s", format);
    int width, height;
    fscanf(final, " %d %d ", &width, &height);
    fscanf(first, "%s", format);
    fscanf(first, " %d %d \n", &width, &height);
    fprintf(new, "%s\n", format);
    fprintf(new, "%d %d\n", width, height);

    int val_final;
    int val_rand;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fscanf(final, "%d", &val_final);
            fscanf(first, "%d", &val_rand);
            int random = rand() % 2;
            if (val_rand ^ random == val_final)
                fprintf(new, "%d ", random);
            else
                fprintf(new, "%d ", abs(random-1));
        }
        fprintf(new, "\n");
    }

    return 0;
}
