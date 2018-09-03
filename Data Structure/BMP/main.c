#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        if (strncmp(argv[1], "-h", 2) == 0 || strncmp(argv[1], "--help", 6) == 0) {
            printf("To extract n pixels from file write:\n./extractStrip -n fileName\n");
            exit(0);
        }
    }

    if (argc != 3) {
        fprintf(stderr, "Error! Wrong number of arguments!\nType ./extractStrip -h or ./extractStrip --help for help\n");
        exit(0);
    }
    
    if (atoi(argv[1]) == 0) {
        fprintf(stderr, "Error! Wrong arguments!\nType ./extractStrip -h or ./extractStrip --help for help\n");
        exit(0);
    }

    readAndCropAndSave(argv[2], abs(atoi(argv[1])));

    return 0;
}