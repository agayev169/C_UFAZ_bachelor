#include <stdio.h>
#include <stdlib.h>
#include "pareto.c"

float **readCSV(char *path, int objectives_n, int objects_n);

int main(int argc, char *argv[]) {
    int objectives_n = 2;
    int objects_n = 21;
    float **data = readCSV("data.csv", objectives_n, objects_n);

    int fronts_n = 0;
    Pareto *fronts = pareto_front(data, objects_n, objectives_n, &fronts_n);

    for (int i = 0; i < fronts_n; i++) {
        printf("Front #%d has %d bikes:\n", i + 1, fronts[i].data_n);
        for (int j = 0; j < fronts[i].data_n; j++) {
            for (int k = 0; k < fronts[i].data_m; k++) {
                printf("%f ", fronts[i].data[j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("Complexity: %d\n", complexity);


    for (int i = 0; i < fronts_n; i++) {
        destruct(&(fronts[i]));
    }
    free(fronts);

    for (int i = 0; i < objects_n; i++) {
        free(data[i]);
    }
    free(data);

    return 0;
}



float **readCSV(char *path, int objectives_n, int objects_n) {
    float **data = (float**) calloc(objects_n, sizeof(float*));
    for (int i = 0; i < objects_n; i++) {
        data[i] = (float*) calloc(objectives_n, sizeof(float));
    }
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Cannot find a file!\n");
        exit(1);
    }

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
        free(tmp);
    }

    fclose(f);
    return data;
}