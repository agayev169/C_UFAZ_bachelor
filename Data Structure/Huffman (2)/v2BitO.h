#ifndef __V2BITO_H__
#define __V2BITO_H__

typedef struct BIT_BUFFER {
    FILE *f;
    unsigned char bits;
    unsigned char position;
} BIT_BUFFER;

void bb_print(BIT_BUFFER *buff);
void bb_fill(BIT_BUFFER *buff, int s, int *bits);

#endif