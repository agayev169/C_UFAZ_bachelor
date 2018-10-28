#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "lifo.h"

typedef struct LinkedListInt {
    int val;
    struct LinkedListInt *next;
} LinkedListInt;

int sortedAdd(LinkedListInt **list, int val);
int add(LinkedListInt **list, int val);
int find(LinkedListInt **list, int n);
int del(LinkedListInt **list, int n);
int printAsc(LinkedListInt *list);
int destroy(LinkedListInt **list);
int printDescR(LinkedListInt *list);
int printDesc(LinkedListInt *list);

#endif
