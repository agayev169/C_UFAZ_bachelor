#include <stdlib.h>
#include <math.h>

char* bits_to_char(int bits[], int size) {
    char* bits_char = (char*) calloc(ceil(size / 8), sizeof(char));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 8 && j < (size - i * 8); j++) {
            bits_char[i] = bits_char[i] << 1;
            bits_char[i] += bits[i + j];
        }
    }
    return bits_char;
}