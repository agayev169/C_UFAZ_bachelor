#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void conversion_base(int *t, int size, int n);
char encode(int x);

int main(int argc, char const *argv[]) {
    int bin[] = {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1};
    int size = 12;
    conversion_base(bin, size, 4);
    printf("\n");


    return 0;
}

void conversion_base(int *t, int sizet, int n) {
    int sizeu, *u;

    sizeu = (sizet / n) + ((sizet % n == 0) ? 0 : 1);
    u = calloc(sizeu, sizeof(int));
    printf("sizet = %d\n", sizet);

    for (int i = 0; i < sizet; i++) {
        u[i / n] += t[i] << (i % n);
    }

    for (int i = sizeu - 1; i >= 0; i--) {
        printf("%c", encode(u[i]));
    }
}

char encode(int x) {
    switch (x) {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
    }
}
