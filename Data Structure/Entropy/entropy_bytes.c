#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

double entropy(long symbols[], long count, long size);

int main(int argc, char *argv[]) {
    // if (argc < 2) {
    //     printf("Usage: %s filename\n", argv[0]);
    //     exit(1);
    // }

    // char *filename = argv[1];
    // int n_bytes = 2;
    // long *symbols = (long*) calloc(pow(2, 8 * n_bytes), sizeof(long));

    // int fd = open(filename, O_RDONLY);
    // if (fd == -1) {
    //     printf("Error! Cannot open a file!\n");
    //     exit(1);
    // }
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

    // char *filename = argv[1];
    int n_bytes = atoi(argv[2]);
    unsigned long size = pow(2, 8 * n_bytes);
    unsigned long *symbols = (long*) calloc(size, sizeof(long));
    printf("n_bytes: %d\nsize: %ld\n", n_bytes, size);

    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error! Cannot open a file!\n");
        exit(1);
    }

    long count = 0;
    if (n_bytes == 1) {
        unsigned char buff[1024];
        int re = 0;
        do {
        re = read(fd, buff, 1024);
            count += re;
            for (int i = 0; i < re; i++) {
                symbols[buff[i]]++;
            }
        } while(re == 1024);
    } else if (n_bytes == 2) {
        unsigned short buff[1024];
        int re = 0;
        do {
        re = read(fd, buff, 1024);
            count += re;
            for (int i = 0; i < re; i++) {
                symbols[buff[i]]++;
            }
        } while(re == 1024);
    } else if (n_bytes == 4) {
        unsigned int *buff = (int*) calloc(1024, sizeof(int));
        int re = 0;
        do {
        re = read(fd, buff, 1024);
            count += re;
            for (int i = 0; i < re; i++) {
                symbols[buff[i]]++;
            }
        } while(re == 1024);
    }

    printf("Entropy: %f\n", entropy(symbols, count, size));
    
    
    close(fd);

    
    return 0;
}

double entropy(long symbols[], long count, long size) {
    double result = 0;
    for (int i = 0; i < size; i++) {
        if (symbols[i] == 0) continue;
        result -= ((double) symbols[i] / (double) count) * log2(((double) symbols[i] /(double) count));
    }
    return result;
} 