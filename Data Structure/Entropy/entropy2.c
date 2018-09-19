#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

float entropy(long symbols[], long count);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];
    long *symbols = (long*) calloc(256, sizeof(long));

    int fd = open("test.txt", O_RDONLY);
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

float entropy(long symbols[], long count) {
    float result = 0;
    for (int i = 0; i < 256; i++) {
        if (symbols[i] == 0) continue;
        result -= ((float) symbols[i] / (float) count) * log2(((float) symbols[i] /(float) count));
    }
    return result;
} 