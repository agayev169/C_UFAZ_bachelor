#include <stdio.h>
#include <stdlib.h>
#include "HuffChar.h"
    // TODO

huff_char *read_header(char *filename, unsigned char *dif, int *size) {
    FILE *f = fopen(filename, "r");
    int size_of_header;
    fread(&size_of_header, 4, 1, f);
    *size = size_of_header / 9;
    huff_char *tab = (huff_char*) calloc(*size, sizeof(huff_char));
    for (int i = 0; i < *size; i++) {
        tab->code = (char*) calloc(8, sizeof(char));
        fread(&(tab[i].c), 1, 1, f);
        fread(tab->code, 1, 8, f);
    }
    fread(dif, 1, 1, f);;
    fclose(f);
    return tab;
}