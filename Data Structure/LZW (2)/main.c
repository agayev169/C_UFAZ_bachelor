#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

int length(char *str);
void char_to_str(int n, char *str);
char *read_file(char *filename);

int main(int argc, char *argv[]) { 
    Vector v;
    reserve(&v, 512);

    for (int i = 0; i < 256; i++) {
        char str[1];
        char_to_str(i, str);
        add(&v, str, 1);
    }

    // for (int i = 0; i < v.size; i++) {
    //     printf("%d: %s\n", i, v.arr[i]);
    // }

    char *str = read_file("test.txt");
    printf("%s", str);

    printf("\n");
    return 0;
}

char *read_file(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Cannot open %s file!\n", filename);
        exit(1);
    }
    fseek(f, SEEK_END, 0);
    int size = ftell(f);
    fseek(f, SEEK_CUR, 0);
    char *str = (char*) calloc(size, sizeof(char));
    // TODO
    fread(f, 1, size, str);
    return str;
}

int length(char *str) {
    int res = 0;
    for (int i = 0; str[i] != '\0'; i++) res++;
    return res;
}

void char_to_str(int n, char *str) {
    str[0] = n;
}