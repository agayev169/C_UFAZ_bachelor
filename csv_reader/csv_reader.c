#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float *readCSV_col(char *path, int col, int *objects_n, char delimiter, char floating_point);

int main(int argc, char *argv[]) {
    int data_size = 0;
    float *data = readCSV("data.csv", 6, &data_size, ';', ',');
    for (int i = 0; i < data_size; i++) {
        printf("%f\n", data[i]);
    }
    free(data);
    return 0;
}


float *readCSV_col(char *path, int col, int *objects_n, char delimiter, char floating_point) {
    const int LINE_LEN = 500;  // Maximum length of a line
    const int WORD_LEN = 32;   // Maximum number of digits in a word
    const int MAX_ROWS = 1000; // Maximum number of rows

    float *data = (float*) calloc(MAX_ROWS, sizeof(float));
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Cannot find a file!\n");
        exit(1);
    }

    *objects_n = 0;
    while (!feof(f) && *objects_n < MAX_ROWS) {
        char *tmp = (char*) calloc(WORD_LEN, sizeof(char));
        char *line = (char*) calloc(LINE_LEN, sizeof(char));
        int i = 0;
        int col_count = 0;
        fscanf(f, "%s", line);
        int line_len = strlen(line);
        for (; i < line_len && col_count < col - 1; i++) {
            if (line[i] == delimiter) col_count++;
        }

        for (int j = 0; j < WORD_LEN && i < line_len && line[i] != delimiter; j++, i++) {
            if (line[i] == floating_point) tmp[j] = '.';
            else tmp[j] = line[i];
        }
        data[(*objects_n)++] = atof(tmp);
        free(line);
        free(tmp);
    }
    data = realloc(data, *objects_n * sizeof(float));

    fclose(f);
    return data;
}