#ifndef __HUFF_CHAR_H__
#define __HUFF_CHAR_H__
    // TODO

typedef struct huff_char {
    char c;
    char *code;
} huff_char;

huff_char *read_header(char *filename, unsigned char *dif, int *size);

#endif