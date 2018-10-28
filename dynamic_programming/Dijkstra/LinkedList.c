#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

int add(LinkedListInt **list, int val, int cost) {
    LinkedListInt *newN;
    if (!(newN = malloc(sizeof(LinkedListInt)))) {
        fprintf(stderr, "Error! No memory to create a new node\n");
        exit(1);
    }
    newN->cost = cost;
    newN->val = val;
    newN->next = *list;
    *list = newN;
    return 0;
}

LinkedListInt *find(LinkedListInt **list, int n) {
    LinkedListInt *tmp = *list;
    while (tmp) {
        if (tmp->val == n) return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

int del(LinkedListInt **list, int n) {
    if ((*list)->val == n) {
        LinkedListInt *temp = (*list);
        *list = (*list)->next;
        return 0;
    }
    for (LinkedListInt *i = *list; i->next != NULL; i = i->next) {
        // printf("Next value: %d\n", i->next->val);
        if (i->next->val == n) {
            LinkedListInt *temp = i;
            i->next = i->next->next;;
            return 0;
        }
    }
    return 1;
}

int printAsc(LinkedListInt *list) {
    for (LinkedListInt *pCur = list; pCur; pCur = pCur->next) {
        printf("Cost: %2d\tValue: %d\tNext: %p\n", pCur->cost, pCur->val, pCur->next);
    }
    return 0;
}

int printNode(LinkedListInt *node) {
    printf("Cost: %2d\tValue: %d\tNext: %p\n", node->cost, node->val, node->next);
    return 0;
}

int destroy(LinkedListInt **list) {
    if (*list != NULL) {
        destroy(&((*list)->next));
        free(*list);
        *list = NULL;
    }
    return 0;
}

LinkedListInt *minCost(LinkedListInt **list, int *cost) {
    LinkedListInt *tmp = *list;
    LinkedListInt *res = *list;
    while (tmp) {
        if (res->cost > tmp->cost) {
            res = tmp;
        }
        tmp = tmp->next;
    }
    *cost = res->cost;
    return res;
}

void parseCosts(LinkedListInt **list, int *costs, int cost_n) {
    LinkedListInt *tmp = *list;
    while (tmp) {
        tmp->cost = costs[tmp->val - 1];
        tmp = tmp->next;
    }
}