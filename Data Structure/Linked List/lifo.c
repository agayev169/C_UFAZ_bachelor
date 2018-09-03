#include <stdio.h>
#include <stdlib.h>
#include "lifo.h"

int constructLifo(Lifo *p, int size) {
    if (!(p->lifo = (int*)calloc(size, sizeof(int)))) {
        fprintf(stderr, "Error! No space to create a lifo!\n");
        exit(1);
    }
    p->size = size;
    p->top = 0;
    return 0;
}

int push(Lifo *p, int n) {
    if (p->top >= p->size) {
        fprintf(stderr, "Error! Lifo is full!\n");
        return 1;
    }
    p->lifo[p->top] = n;
    p->top++;
    return 0;
}

int pop(Lifo *p, int *ans) {
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
    // printf("Poped value: %d\n", *ans);
    return 0;
}

int setSize(Lifo *p, int size) {


    return 0;
}

int printTop(Lifo p) {
    if (p.size == 0) {
        fprintf(stderr, "Error in printTop function! Lifo is not created!\n");
        return 1;
    } else if (p.top == 0) {
        fprintf(stderr, "Error in printTop function! Lifo is empty!\n");
        return 2;
    } else
        printf("%d\n", p.lifo[p.top - 1]);
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
            printf("Value of member #%d = %d\n", i, p.lifo[i]);
}

int destructLifo(Lifo *p) {
    free(p->lifo);
    return 0;
}

int isEmpty(Lifo *p) {
    return p->top == 0 ? 1 : 0;
}
