#include <stdio.h>

int main() {
    int data[2][3];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%p ", &data[i][j]);
        }
        printf("\n");
    }

    return 0;
}