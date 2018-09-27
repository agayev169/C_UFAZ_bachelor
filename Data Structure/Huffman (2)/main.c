#include <stdio.h>
#include <math.h>
#include <string.h>
#include "readOf.h"

char* bits_to_char(int bits[], int size);

int main(int argc, char *argv[]) {
    FILE *out = fopen("out.txt", "wb");

    int bits[7] = {1, 0, 0, 1, 1, 1, 1};
    char* bits_char = bits_to_char(bits, 7);

    fclose(out);

    // HuffChar *tab = (HuffChar*) calloc(8, sizeof(HuffChar));
    // tab[0].l = 't';
    // strcpy(tab[0].bitstab, "00");
    // tab[1].l = 'n';
    // strcpy(tab[1].bitstab, "01");
    // tab[2].l = 'o';
    // strcpy(tab[2].bitstab, "10");
    // tab[3].l = 'i';
    // strcpy(tab[3].bitstab, "11000");
    // tab[4].l = 's';
    // strcpy(tab[4].bitstab, "11001");
    // tab[5].l = 'm';
    // strcpy(tab[5].bitstab, "11010");
    // tab[6].l = 'd';
    // strcpy(tab[6].bitstab, "11011");
    // tab[7].l = ' ';
    // strcpy(tab[7].bitstab, "111");

    // writeBinaryFile(out, 8, tab);
    // fclose(out);


    // FILE *in = fopen("out.txt", "rb");
    // readBinaryFile(in);

    // fclose(in);

    return 0;
}