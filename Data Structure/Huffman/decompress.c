#include <stdio.h>
#include <stdlib.h>
#include "HuffChar.h"

int main(int argc, char *argv[]) {
    // TODO
    unsigned char dif;
    int size_of_tab;
    huff_char *tab = read_header("test_bin.bin", &dif, &size_of_tab);
    for (int i = 0; i < size_of_tab; i++) {
        printf("%c: %s\n", tab[i].c, tab[i].code);
    }
    free(tab);
    return 0;
}
