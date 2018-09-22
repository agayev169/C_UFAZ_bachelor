// Burrows-Wheeler Transform

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transform(char *str);
int length(char *str);
char **all_rotations(char *str, int size);
void sort(char **all_rots, int rows, int cols);
void swap(char **all_rots, int n, int m);

void detransform(char *str);
char **create_table(char *str, int size);

int main(int argc, char *argv[]) {
    char str[140];
    printf("String: ");
    scanf("%[^\n]s", str);
    // strcat(str, "|");
    detransform(str);

    return 0;
}

void transform(char *str) {
    int size = length(str);
    char **all_rots = all_rotations(str, size);
    sort(all_rots, size, size);
    for (int i = 0; i < size; i++) {
        str[i] = all_rots[i][size - 1];
    }

    for (int i = 0; i < size; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
}

int length(char *str) {
    int size = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        size++;
    }
    return size;
}

char **all_rotations(char *str, int size) {
    char **all_rots = (char**) calloc(size, sizeof(char*));
    for (int i = 0; i < size; i++) {
        all_rots[i] = (char*) calloc(size, sizeof(char));
        for (int j = 0; j < size; j++) {
            all_rots[i][j] = str[(i + j) % size];
        }
    }
    return all_rots;
}

void sort(char **all_rots, int rows, int cols) {
    for (int i = 1; i < rows; i++) {
        for (int j = i; j > 0; j--) {
            for (int k = 0; k < cols; k++) {
                if (all_rots[j][k] < all_rots[j - 1][k]) {
                    swap(all_rots, j - 1, j);
                    break;
                } else if (all_rots[j][k] > all_rots[j - 1][k]) {
                    break;
                }
            }
        }
    }
}

void swap(char **all_rots, int n, int m) {
    char *tmp = all_rots[n];
    all_rots[n] = all_rots[m];
    all_rots[m] = tmp;
}

void detransform(char *str) {
    int size = length(str);
    char **table = create_table(str, size);
    sort(table, size, 1);

    for (int i = 0; i < size - 1; i++) {
        char **new_table = create_table(str, size);
        for (int j = 0; j < size; j++) {
            strcat(new_table[j], table[j]);
            table[j] = (char*) calloc(i + 2, sizeof(char));
            strcpy(table[j], new_table[j]);
        }
        sort(table, size, i + 2);
    }

    for (int i = 0; i < size; i++) {
        if (table[i][size - 1] == '|') {
            printf("%s\b \n", table[i]);
        }
    }
}


char **create_table(char *str, int size) {
    char **table = (char**) calloc(size, sizeof(char*));
    for (int i = 0; i < size; i++) {
       table[i] = (char*) calloc(1, sizeof(char)); 
       table[i][0] = str[i];
    }
    return table;
}