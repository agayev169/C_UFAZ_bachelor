#include <stdio.h>
#include <stdlib.h>

float **readCSV(char *path, int objectives_n, int objects_n);
float **pareto_front(float **data, int n, int m, int *count);
void delete_same(float **from, int from_n, float **orig, int orig_n, int m);
void delete(float **from, int from_n, int m, int index);

int complexity = 0;

int main(int argc, char *argv[]) {
    int objectives_n = 2;
    int objects_n = 21;
    float **data = readCSV("data.csv", objectives_n, objects_n);

    int front_n = 1;
    while (objects_n > 0) {
        int count = 0;
        float **pareto = pareto_front(data, objects_n, objectives_n, &count);

        printf("We have %d bike(s) in Pareto front #%d:\n", count, front_n);
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < objectives_n; j++) {
                printf("%f ", pareto[i][j]);
            }
            printf("\n");
        }
        delete_same(data, objects_n, pareto, count, objectives_n);
        objects_n -= count;
        front_n++;

        printf("\n\n");
        free(pareto);
    }

    printf("Complexity: %d\n", complexity);

    free(data);

    return 0;
}

void delete(float **from, int from_n, int m, int index) {
    float tmp[m];
    for (int i = 0; i < m; i++) {
        from[index][i] = from[from_n - 1][i];
    }
}

void delete_same(float **from, int from_n, float **orig, int orig_n, int m) {
    for (int i = 0; i < orig_n; i++) {
        for (int j = 0; j < from_n; j++) {
            char same = 1;
            for (int k = 0; k < m; k++) {
                if (orig[i][k] != from[j][k]) {
                    same = 0;
                }
            }
            if (same) {
                delete(from, from_n--, m, j);
            }
        }
    }
}

float **pareto_front(float **data, int objects_n, int objectives_n, int *count) {
    float **pareto = (float**) calloc(objects_n, sizeof(float*));
    for (int i = 0; i < objects_n; i++) {
        pareto[i] = (float*) calloc(objectives_n, sizeof(float));
    }

    *count = 0;
    for (int i = 0; i < objects_n; i++) {
        char is_dominant = 1;
        for (int j = 0; j < objects_n; j++) {
            if (i == j) continue;
            int domin = 0;
            for (int k = 0; k < objectives_n; k++) {
                if (data[i][k] > data[j][k]) {
                    domin++;
                    complexity++;
                }
            }
            if (domin == objectives_n) {
                is_dominant = 0;
                break;
            }
        }
        if (is_dominant) {
            for (int k = 0; k < objectives_n; k++) {
                pareto[*count][k] = data[i][k];
            }
            (*count)++;
        }
    }
    return pareto;
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