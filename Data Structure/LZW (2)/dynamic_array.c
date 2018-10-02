#include "dynamic_array.h"
#include <stdlib.h>

// Reserves size values in Vector v
void reserve(Vector *v, int size) {
    v->arr = (char**) calloc(size, sizeof(char*));
    v->max_size = size;
    v->size = 0;
}

void add(Vector *v, char *str, int str_size) {
    if (is_full(*v))
        expand(v);
    v->arr[v->size] = (char*) calloc(str_size, sizeof(char));
    for (int i = 0; i < str_size; i++) {
        v->arr[v->size][i] = str[i];
    }
    v->size++;
}

void expand(Vector *v) {
    v->arr = (char**) realloc(v->arr, v->max_size * 2 * sizeof(char*));
    v->max_size *= 2;
}

int is_full(Vector v) {
    return v.max_size == v.size;
}