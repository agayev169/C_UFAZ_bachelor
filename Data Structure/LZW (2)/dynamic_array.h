#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

typedef struct Vector {
    char **arr;
    int size;
    int max_size;
} Vector;

void reserve(Vector *v, int size);
void add(Vector *v, char *str, int str_size);
void expand(Vector *v);
int is_full(Vector v);

#endif