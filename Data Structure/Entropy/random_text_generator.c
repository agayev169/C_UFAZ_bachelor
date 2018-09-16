#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_LETTERS 100000
#define MAX_LETTERS 200000

void generate(char *filename);

int main(int argc, char *argv[]) {
    char *filename = "in.txt";
    srand(time(NULL));
    generate(filename);

    return 0;
}

void generate(char *filename) {
    FILE *file;
    file = fopen(filename, "w");
    int size = rand() % (MAX_LETTERS - MIN_LETTERS) + MIN_LETTERS;
    printf("Size: %d\n", size);
    for (int i = 0; i < size; i++) {
        char c = rand() % 255;
        fwrite(&c, 1, 1, file);
    }
    fclose(file);
}