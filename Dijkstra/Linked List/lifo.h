#ifndef _LIFO_H
#define _LIFO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Lifo {
    int top;
    int size;
    int *lifo;
} Lifo;

int constructLifo(Lifo *p, int size);
int setSize(Lifo *p, int size); // if size < size of Lifo - enlarge, else be careful to not to lost the data
int push(Lifo *p, int n);
int pop(Lifo *p, int *ans);
int print(Lifo p);
int printTop(Lifo p);
int destructLifo(Lifo *p);
int isEmpty(Lifo *p);

#endif
