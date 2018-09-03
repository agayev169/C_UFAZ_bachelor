#include <stdio.h>

int main() {
    FILE *f;
    if ((f = fopen("ints.txt", "r")) != NULL) {
        int x;
        fscanf(f, "%d", &x);
        while (!feof(f)) {
            printf("%d\n", x);
            fscanf(f, "%d", &x);
        }

        fclose(f);
        return 0;
    }
    else {
        printf("404\n");
    }
}