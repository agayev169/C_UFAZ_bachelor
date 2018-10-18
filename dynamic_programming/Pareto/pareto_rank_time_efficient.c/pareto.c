#include <stdio.h>
#include <stdlib.h>

typedef struct ParetoList {
    float *vals;
    struct ParetoList *next;
} ParetoList;

void PL_add(ParetoList **list, float *vals, int vals_n, int vals_m);
void PL_remove(ParetoList **list, float **vals, int vals_n, int vals_m);
void PL_destruct(ParetoList **list);

typedef struct Pareto {
    float **data;
    int data_n;
    int data_m;
    int *front_index;
    int *dominants_n;
    ParetoList **slaves;
} Pareto;

Pareto *pareto_front(float **data, int n, int m, int *size);
void delete_same(float **from, int from_n, Pareto pareto);
void delete(float **from, int from_n, int m, int index);
int find_in_pareto(Pareto pareto, float *vals);
Pareto parse_front(Pareto *pareto);
void destruct(Pareto *pareto);
char has_front(Pareto pareto);

int complexity = 0;

void PL_add(ParetoList **list, float *vals, int vals_n, int vals_m) {
    if (!(*list)) { // Empty list
        *list = calloc(1, sizeof(ParetoList));
        (*list)->vals = (float*) calloc(vals_m, sizeof(float));
        for (int i = 0; i < vals_m; i++) {
            (*list)->vals[i] = vals[i];
        }
        (*list)->next = NULL;
    } else {
        ParetoList *tmp = *list;
        while (tmp->next) { // Find the last element
            tmp = tmp->next;
        }
        ParetoList *node = calloc(1, sizeof(ParetoList));
        node->vals = (float*) calloc(vals_m, sizeof(float));
        for (int i = 0; i < vals_m; i++) {
            node->vals[i] = vals[i];
        }
        node->next = NULL;
        tmp->next = node;
    }
}

void PL_destruct(ParetoList **list) {
    while (*list) {
        ParetoList *tmp = *list;
        *list = (*list)->next;
        if (tmp->vals) free(tmp->vals);
        free(tmp);
    }
}

// --------------------------Pareto functions----------------


char has_front(Pareto pareto) {
    char has_front = 0;
    for (int i = 0; i < pareto.data_n; i++) {
        if (pareto.front_index[i] <= 0) return 1;
    }
    return 0;
}

void destruct(Pareto *pareto) {
    for (int i = 0; i < pareto->data_n; i++) {
        // if (pareto->data[i]) free(pareto->data[i]);
        free(pareto->data[i]);
        // if (pareto->slaves[i]) PL_destruct(&(pareto->slaves[i]));
    }
    if (pareto->data) free(pareto->data);
    if (pareto->slaves) free(pareto->slaves);
    if (pareto->front_index) free(pareto->front_index);
    if (pareto->dominants_n) free(pareto->dominants_n);
}

void delete(float **from, int from_n, int m, int index) {
    for (int i = 0; i < m; i++) {
        from[index][i] = from[from_n - 1][i];
    }
}

void delete_same(float **from, int from_n, Pareto pareto) {
    for (int i = 0; i < pareto.data_n; i++) {
        for (int j = 0; j < from_n; j++) {
            char same = 1;
            for (int k = 0; k < pareto.data_m; k++) {
                if (pareto.data[i][k] != from[j][k]) {
                    same = 0;
                }
            }
            if (same) {
                delete(from, from_n--, pareto.data_m, j);
                i--;
                break;
            }
        }
    }
}

Pareto parse_front(Pareto *pareto) {
    Pareto front;
    front.slaves = NULL;
    front.front_index = NULL;
    front.dominants_n = NULL;
    front.data_m = pareto->data_m;
    float **data = (float**) calloc(pareto->data_n, sizeof(float*));
    for (int i = 0; i < pareto->data_n; i++) {
        data[i] = (float*) calloc(front.data_m, sizeof(float));
    }

    int count = 0;
    for (int i = 0; i < pareto->data_n; i++) {
        if (pareto->dominants_n[i] <= 0) {
            if (pareto->front_index[i] == 1) { // New front
                for (int j = 0; j < pareto->data_m; j++) {
                    data[count][j] = pareto->data[i][j];
                }
                count++;
                ParetoList *tmp = pareto->slaves[i];
                while (tmp) {
                    int index = find_in_pareto(*pareto, tmp->vals);
                    pareto->dominants_n[index]--;
                    tmp = tmp->next;
                }
                PL_destruct(&(pareto->slaves[i]));
            }
            pareto->front_index[i]++;
        }
    }

    front.data = (float**) calloc(count, sizeof(float*));
    for (int i = 0; i < count; i++) {
        front.data[i] = (float*) calloc(front.data_m, sizeof(float));
        for (int j = 0; j < pareto->data_m; j++) {
            front.data[i][j] = data[i][j];
        }
    }

    for (int i = 0; i < pareto->data_n; i++) {
        free(data[i]);
    }

    free(data);
    front.data_n = count;
    return front;
}

int find_in_pareto(Pareto pareto, float *vals) {
    for (int i = 0; i < pareto.data_n; i++) {
        char same = 1;
        for (int j = 0; j < pareto.data_m; j++) {
            if (pareto.data[i][j] != vals[j]) {
                same = 0;
                break;
            }
        }
        if (same) return i;
    }
}

Pareto *pareto_front(float **data, int objects_n, int objectives_n, int *size) {
    Pareto *fronts = (Pareto*) calloc(objects_n, sizeof(Pareto));
    *size = 0;
    Pareto pareto;
    pareto.data = (float**) calloc(objects_n, sizeof(float*));
    pareto.data_n = objects_n;
    pareto.data_m = objectives_n;
    for (int i = 0; i < objects_n; i++) {
        pareto.data[i] = (float*) calloc(objectives_n, sizeof(float));
    }
    pareto.slaves = calloc(objects_n, sizeof(ParetoList));
    for (int i = 0; i < objects_n; i++) {
        pareto.slaves[i] = NULL;
    }
    pareto.dominants_n = (int*) calloc(objects_n, sizeof(int));

    pareto.front_index = (int*) calloc(objects_n, sizeof(int));

    for (int i = 0; i < objects_n; i++) {
        for (int k = 0; k < objectives_n; k++) {
            pareto.data[i][k] = data[i][k];
        }
        char is_dominanted = 0;
        for (int j = 0; j < objects_n; j++) {
            if (i == j) continue;
            int dominated_by = 0;
            int dominated = 0; 
            for (int k = 0; k < objectives_n; k++) {
                if (data[i][k] > data[j][k]) {
                    dominated_by++;
                    complexity++;
                } else if (data[i][k] < data[j][k]) {
                    dominated++;
                    complexity++;
                }
            } 
            if (dominated_by == objectives_n) {
                is_dominanted = 1;
                pareto.dominants_n[i]++;
            }
            if (dominated == objectives_n) {
                PL_add(&(pareto.slaves[i]), data[j], objects_n, objectives_n);
            }
        }
        if (!is_dominanted) {
            for (int k = 0; k < objectives_n; k++) {
                pareto.front_index[i] = 1;
            }
        }
    }

    char has_front_n = 0;
    while (1) {
        if (has_front_n >= 1) break;
        if (!has_front(pareto)) has_front_n++;
        fronts[(*size)++] = parse_front(&pareto);
    }
    fronts = realloc(fronts, *size * sizeof(Pareto));
    destruct(&pareto);
    return fronts;
}