// Burrows-Wheeler Transform

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transform(char *filename_in, char *filename_out);
char *read_file(FILE *f);
int length(FILE *f);
char **all_rotations(char *str, int size);
void sort(char **all_rots, int rows, int cols);
void swap(char **all_rots, int n, int m);

void detransfrom(char *filename_in, char *filename_out);
char **create_table(char *str, int size);

int main(int argc, char *argv[]) {
    // char *filename_in = "in.txt";
    // char *filename_out = "out.txt";
    // transform(filename_in, filename_out);
    char *filename_in = "out.txt";
    char *filename_out = "out2.txt";
    detransfrom(filename_in, filename_out);
    return 0;
}

void transform(char *filename_in, char *filename_out) {
    FILE *f_in = fopen(filename_in, "r");
    FILE *f_out = fopen(filename_out, "w");

    char *str = read_file(f_in);
    printf("Str: %s\n", str);
    int size = length(f_in);
    char **all_rots = all_rotations(str, size);
    sort(all_rots, size, size);
    for (int i = 0; i < size; i++) {
        str[i] = all_rots[i][size - 1];
    }

    for (int i = 0; i < size; i++) {
        fprintf(f_out, "%c", str[i]);
    }

    fclose(f_in);
    fclose(f_out);
}

int length(FILE *f) {
    fseek(f, 0, SEEK_SET);
    int size = 0;
    while(!feof(f)) {
        char c;
        fread(&c, 1, 1, f);
        size++;
    }
    // printf("Size: %d\n", size);
    return size - 1;
}

char *read_file(FILE *f) {
    int size = length(f);

    fseek(f, 0, SEEK_SET);
    char *str = (char*) calloc(size, sizeof(char));
    fread(str, 1, size, f);
    return str;
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

void detransfrom(char *filename_in, char *filename_out) {
    FILE *f_in = fopen(filename_in, "r");
    FILE *f_out = fopen(filename_out, "w");

    char *str = read_file(f_in);
    int size = length(f_in);
    printf("%s, %d\n", str, size);
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
        if (table[i][size - 1] == '$') {
            fprintf(f_out, "%s", table[i]);
            printf("%s\n", table[i]);
        }
    }

    fclose(f_in);
    fclose(f_out);
}

char **create_table(char *str, int size) {
    char **table = (char**) calloc(size, sizeof(char*));
    for (int i = 0; i < size; i++) {
       table[i] = (char*) calloc(1, sizeof(char)); 
       table[i][0] = str[i];
    }

    return table;
}