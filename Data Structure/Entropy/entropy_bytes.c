#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

double entropy_of_file(char *filename, int n_bytes);
double entropy(long symbols[], long count, long size);

int main(int argc, char *argv[]) {
    char c;
    char *filename = argv[3];
    while((c = getopt(argc, argv, "a:")) != -1) {
        switch(c) {
            case 'a':
                printf("Your choice: %d\n", atoi(argv[2]));
                break;
            case '?':
                if (optopt == 'a') {
                    printf("You have to specify the number of bytes\n");
                    exit(0);
                }
        }
    }

    int n_bytes = atoi(argv[2]);        
    double entropy = entropy_of_file(filename, n_bytes);
    printf("Entropy: %lf\n", entropy);

    return 0;
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