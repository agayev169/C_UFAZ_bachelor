#include <stdio.h>
#include "bayer-moode.c"

int main(int argc, char *argv[]) {
    char word[]    = "bbcacbabaca";
    char to_find[] = "babac";
    
    printf("index: %d\n", find_in_word(to_find, word));

    return 0;
}
