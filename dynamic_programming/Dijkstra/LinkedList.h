#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListInt {
    int cost;
    int val;
    struct LinkedListInt *next;
} LinkedListInt;

int add(LinkedListInt **list, int val, int cost);
LinkedListInt *find(LinkedListInt **list, int n);
int del(LinkedListInt **list, int n);
int printAsc(LinkedListInt *list);
int destroy(LinkedListInt **list);
LinkedListInt *minCost(LinkedListInt **list, int *cost);
void parseCosts(LinkedListInt **list, int *costs, int cost_n);

#endif
