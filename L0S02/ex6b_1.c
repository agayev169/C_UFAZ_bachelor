// Create a file give it any NAME, write inside of it integer numbers separated by space. And finally save the file in
// the format .txt . Example: NAME.txt
#include <stdio.h>

int main() {
    FILE *f = fopen("ints.txt", "w");

    int x;
    scanf("%d", &x);
    while (x != EOF) {
        fprintf(f, "%d ", x);
        scanf("%d", &x);
    }

    fclose(f);
    return 0;
}