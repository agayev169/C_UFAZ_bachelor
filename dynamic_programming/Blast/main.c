#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "genome.c"

char *random_string(int size, char *letters, int letters_size);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    // printf("%s\n", random_string(10, "ACGT", 4));
    char *matches = (char*) calloc(20, sizeof(char));
    for (int i = 0; i < 20; i++) {
        if (rand() % 2) matches[i] = -1;
        else matches[i] = 1;
        printf("%d ", matches[i]);
    }
    printf("\n");
    

    int *dif = difference(matches, 20);
    for (int i = 0; i < 21; i++) {
        printf("%d ", dif[i]);
    }
    printf("\n");
    int *globals = max_subarray(matches, 20);
    printf("%d %d %d\n", globals[0], globals[1], globals[2]);

    free(matches);
    free(dif);
    free(globals);

    return 0;
}

char *random_string(int size, char *letters, int letters_size) {
    char *str = (char*) calloc(size, sizeof(char));
    for (int i = 0; i < size; i++) {
        int index = rand() % letters_size;
        str[i] = letters[index];
    }
    return str;
}