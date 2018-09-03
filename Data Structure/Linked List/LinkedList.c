#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "lifo.h"

int sortedAdd(LinkedListInt **list, int val) {
    if (*list) {
        LinkedListInt *temp = *list;
        if (temp->val > val) {
            add(list, val);
            return 0;
        }
        while (temp != NULL) {
            LinkedListInt *temp2 = temp->next;
            if ((temp2 && temp2->val > val) || !temp2) {
                LinkedListInt *newN;
                if (!(newN = malloc(sizeof(LinkedListInt)))) {
                    fprintf(stderr, "Error! No memory to create a new node\n");
                    exit(1);
                }
                newN->val = val;
                newN->next = temp2;
                temp->next = newN;
                return 0;
            }
            temp2 = temp;
            temp = temp->next;
        }
    } else {
        add(list, val);
    }
    return 0;
}

int add(LinkedListInt **list, int val) {
    LinkedListInt *newN;
    if (!(newN = malloc(sizeof(LinkedListInt)))) {
        fprintf(stderr, "Error! No memory to create a new node\n");
        exit(1);
    }
    newN->val = val;
    newN->next = *list;
    *list = newN;
    return 0;
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
        printf("Value: %d\tNext: %p\n", pCur->val, pCur->next);
    }
    return 0;
}

int printDescR(LinkedListInt *list) {
    if (list) {
        printDescR(list->next);
        printf("%d<--", list->val);
    }
    return 0;
}

int printDesc(LinkedListInt *list) {
    Lifo stack;
    constructLifo(&stack, 10);
    for (LinkedListInt *pCur = list; pCur; pCur = pCur->next) {
        push(&stack, pCur->val);
    }
    while (!isEmpty(&stack)) {
        int temp;
        pop(&stack, &temp);
        printf("%d<--", temp);
    }
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
