#include <stdio.h>
#include <stdlib.h>
#include "lifo.h"

int constructLifo(Lifo *p, int size) {
    if (!(p->lifo = (double*)calloc(size, sizeof(double)))) {
        fprintf(stderr, "Error! No space to create a lifo!\n");
        exit(1);
    }
    p->size = size;
    p->top = 0;
    return 0;
}

int push(Lifo *p, double n) {
    if (p->top >= p->size) {
        fprintf(stderr, "Error! Lifo is full!\n");
        return 1;
    }
    p->lifo[p->top] = n;
    p->top++;
    return 0;
}

int pop(Lifo *p, double *ans) {
    // *ans = 0;
    if (p->size == 0) {
        fprintf(stderr, "Error in pop function! Lifo is not created!\n");
        return 1;
    } else if (p->top == 0) {
        fprintf(stderr, "Error in pop function! Lifo is empty!\n");
        return 2;
    }
    *ans = p->lifo[p->top-1];
    p->top--;
    // printf("Poped value: %lf\n", *ans);
    return 0;
}

double top(Lifo p) {
    if (p.size == 0) {
        fprintf(stderr, "Error in top function! Lifo is not created!\n");
        return 1;
    } else if (p.top == 0) {
        fprintf(stderr, "Error in printTop function! Lifo is empty!\n");
        return 2;
    } else {
        return p.lifo[p.top - 1];
    }
}

int printTop(Lifo p) {
    if (p.size == 0) {
        fprintf(stderr, "Error in printTop function! Lifo is not created!\n");
        return 1;
    } else if (p.top == 0) {
        fprintf(stderr, "Error in printTop function! Lifo is empty!\n");
        return 2;
    } else
        printf("%lf\n", p.lifo[p.top - 1]);
    return 0;
}

int print(Lifo p) {
    if (p.size == 0) {
        fprintf(stderr, "Error in print function! Lifo is not created!\n");
        return 1;
    } else if (p.top == 0) {
        fprintf(stderr, "Error in print function! Lifo is empty!\n");
        return 2;
    } else
        for (int i = 0; i < p.top; i++)
            printf("Value of member #%d = %lf\n", i, p.lifo[i]);
    return 0;
}

int destructLifo(Lifo *p) {
    free(p->lifo);
    return 0;
}
