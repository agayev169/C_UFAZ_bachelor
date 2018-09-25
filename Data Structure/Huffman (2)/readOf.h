#ifndef __READ_OF_H__
#define __READ_OF_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct HuffChar {
    char l;
    char bitstab[8];
} HuffChar;

void writeBinaryFile(FILE *file, int size, HuffChar tab[], char *str);
char *readBinaryFile(FILE *file);

#endif