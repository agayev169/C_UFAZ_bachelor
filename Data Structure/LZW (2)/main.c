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
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *str = (char*) calloc(size, sizeof(char));
    fread(str, 1, size, f);
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