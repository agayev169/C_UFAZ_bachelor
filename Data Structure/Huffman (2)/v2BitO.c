#include <stdio.h>
#include <stdlib.h>
#include "v2BitO.h"

void bb_print(BIT_BUFFER *buff) {
    if (buff->pos == 0) return;

    while (buff->pos < 8) {
        buff->bits = buff->bits & ~(1 << 8 - buff->pos - 1);
        buff->pos++;
    }
    fwrite(&(buff->bits), sizeof(char), 1, buff->f);
    buff->pos = 0;
    buff->bits = 0;
}

void bb_fill(BIT_BUFFER *buff, int s, int *bits) {
    int shift_pos;
    for (int i = 0; i < s; i++) {
        if (buff->pos == 8) bb_print(buff);
        shift_pos = 8 - buff->pos - 1;
        if (bits[i] == 1) buff->bits = buff->bits | (1 << shift_pos);
        else buff->bits = buff->bits & (0 << shift_pos);
        buff->pos++;
    }
}