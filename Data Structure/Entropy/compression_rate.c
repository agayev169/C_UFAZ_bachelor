#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

long len(char *filename);
double entropy_of_file(char *filename, int n_bytes);
double entropy(long symbols[], long count, long size);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    double entropy = entropy_of_file(argv[1], 1);
    long size = len(argv[1]);
    printf("Size: %ld\n", size);
    printf("Entropy: %lf\n", entropy);
    double compression_rate = (double) size / (pow(2, ceil(entropy)));
    printf("Compression rate: %lf\n", compression_rate);

    return 0;
}

long len(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error! Cannot open a file!\n");
        exit(1);
    }

    long count = 0;
    int re;
    char buff[1024];
    while ((re = read(fd, buff, 1024)) != 0) {
        count += re;
    }

    return count;
}

double entropy_of_file(char *filename, int n_bytes) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error! Cannot open a file!\n");
        exit(1);
    }

    unsigned long size = pow(2, 8 * n_bytes);
    unsigned long *symbols = (long*) calloc(size, sizeof(long));

    long count = 0;
    if (n_bytes == 1) {
        unsigned char *buff = (char*) calloc(1024, sizeof(char));
        int re = 0;
        do {
        re = read(fd, buff, 1024);
            count += re;
            for (int i = 0; i < re; i++) {
                symbols[buff[i]]++;
            }
        } while(re == 1024);
    } else if (n_bytes == 2) {
        unsigned short *buff = (short*) calloc(1024, sizeof(short));
        int re = 0;
        do {
        re = read(fd, buff, 1024);
            count += re;
            for (int i = 0; i < re; i++) {
                symbols[buff[i]]++;
            }
        } while(re == 1024);
    }

    double ent = entropy(symbols, count, size);
    free(symbols);

    close(fd);
    return ent;
}

double entropy(long symbols[], long count, long size) {
    double result = 0;
    for (int i = 0; i < size; i++) {
        if (symbols[i] == 0) continue;
        result -= ((double) symbols[i] / (double) count) * log2(((double) symbols[i] /(double) count));
    }
    return result;
} 