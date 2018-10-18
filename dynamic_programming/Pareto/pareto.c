#include <stdio.h>
#include <stdlib.h>

float **readCSV(char *path, int objectives_n, int objects_n);

int main(int argc, char *argv[]) {
    int objectives_n = 2;
    int objects_n = 20;
    float **data = readCSV("data.csv", objectives_n, objects_n);

    float **pareto = (float**) calloc(objects_n, sizeof(float*));
    for (int i = 0; i < objects_n; i++) {
        pareto[i] = (float*) calloc(objectives_n, sizeof(float));
    }


    int count = 0;
    for (int i = 0; i < objects_n; i++) {
        char is_dominant = 1;
        for (int j = 0; j < objects_n; j++) {
            if (i == j) continue;
            int domin = 0;
            for (int k = 0; k < objectives_n; k++) {
                if (data[i][k] > data[j][k]) {
                    domin++;
                }
            }
            if (domin == objectives_n) {
                is_dominant = 0;
                break;
            }
        }
        if (is_dominant) {
            for (int k = 0; k < objectives_n; k++) {
                pareto[count][k] = data[i][k];
            }
            count++;
        }
    }

    printf("We have %d bikes in Pareto front:\n", count);
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < objectives_n; j++) {
            printf("%f ", pareto[i][j]);
        }
        printf("\n");
    }

    free(data);
    free(pareto);

    return 0;
}

float **readCSV(char *path, int objectives_n, int objects_n) {
    float **data = (float**) calloc(objects_n, sizeof(float*));
    for (int i = 0; i < objects_n; i++) {
        data[i] = (float*) calloc(objectives_n, sizeof(float));
    }
    FILE *f = fopen(path, "r");

    int i = 0;
    int j = 0;
    while (!feof(f)) {
        if (j > 1) {
            j = 0;
            i++;
        }
        char *tmp = (char*) calloc(20, sizeof(char*));
        int k = 0;
        while (1) {
            fscanf(f, "%c", &(tmp[k]));
            if ((tmp[k] > '9' || tmp[k] < '0') && tmp[k] != '.') break;
            k++;
        }
        data[i][j] = atof(tmp);
        j++;
    }

    fclose(f);
    return data;
}