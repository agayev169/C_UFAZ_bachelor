#include "readOf.h"

void writeBinaryFile(FILE *file, int size, HuffChar tab[]) {
    // Saving the table
    putw(size, file);
    for (int i = 0; i < size; i++)
        fwrite(&tab[i], sizeof(HuffChar), 1, file);
    
    // Saving the compressed text
}

char *readBinaryFile(FILE *file) {
    // Reading the table
    int num = getw(file);
    printf("The number of characters in the table: %d\n", num);
    HuffChar newch;
    while (!feof(file)) {
        fread(&newch, sizeof(HuffChar), 1, file);
        printf("Char %c: %s\n", newch.l, newch.bitstab);
    }

    return NULL;
    // Reading the compressed text
}