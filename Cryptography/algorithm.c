#include <stdio.h>

int main(int argc, char const *argv[]) {
    FILE *random = fopen("rand.ppm", "r");
    FILE *first = fopen("second.ppm", "r");
    FILE *final = fopen("final.ppm", "w");

    char format[3];
    fscanf(random, "%s", format);
    int width, height;
    fscanf(random, " %d %d ", &width, &height);
    fprintf(final, "%s\n", format);
    fprintf(final, "%d %d\n", width, height);

    int val_first;
    int val_rand;
    fscanf(first, "%s", format);
    fscanf(first, " %d %d \n", &width, &height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fscanf(random, "%d", &val_rand);
            fscanf(first, "%d", &val_first);
            fprintf(final, "%d ", val_rand ^ val_first);
        }
        fprintf(final, "\n");
    }

    return 0;
}
