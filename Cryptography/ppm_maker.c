#include <stdio.h>

int main(int argc, char const *argv[]) {
    FILE *f = fopen("final2.ppm", "r");
    FILE *n = fopen("final.ppm", "w");
    char format[3];
    fscanf(f, "%s", format);
    fprintf(n, "P1\n");
    int width, height;
    fscanf(f, "%d %d", &width, &height);
    fprintf(n, "%d %d\n", width, height);
    int val;
    fscanf(f, "%d", &val);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fscanf(f, "%d", &val);
            fscanf(f, "%d", &val);
            fscanf(f, "%d", &val);
            if (val == 0) fprintf(n, "1 ");
            else fprintf(n, "0 ");
        }
        fprintf(n, "\n");
    }
    return 0;
}
