#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

double entropy(long symbols[], long count);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];
    long *symbols = (long*) calloc(256, sizeof(long));

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error! Cannot open a file!\n");
        exit(1);
    }

    int count = 0;
    unsigned char buff[1024];
    int re = 0;
    do {
    re = read(fd, buff, 1024);
        count += re;
        for (int i = 0; i < re; i++) {
            symbols[buff[i]]++;
        }
    } while(re == 1024);

    printf("Entropy: %f\n", entropy(symbols, count));
    
    close(fd);
    
    return 0;
}

double entropy(long symbols[], long count) {
    double result = 0;
    for (int i = 0; i < 256; i++) {
        if (symbols[i] == 0) continue;
        result -= ((double) symbols[i] / (double) count) * log2(((double) symbols[i] /(double) count));
    }
    return result;
} 