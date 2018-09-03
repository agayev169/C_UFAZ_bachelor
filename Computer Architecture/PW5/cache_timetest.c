#include <stdio.h>
#include <time.h>

int main() {
    clock_t t = clock();
    int data[1024][1024];
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            data[i][j] = 0;
        }
    }
    printf("%ld\n", t);

    return 0;
}