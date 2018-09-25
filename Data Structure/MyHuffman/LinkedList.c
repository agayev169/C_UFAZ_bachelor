#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void LLAdd(LinkedList **list, int val, char c) {
    LinkedList *tmp = (LinkedList*) calloc(1, sizeof(LinkedList));
    tmp->val = val;
    tmp->c = c;
    tmp->next = *list;
    *list = tmp;
}

void LLPrint(LinkedList *list) {
    while (list) {
        printf("[%d, %c] ==> ", list->val, list->c);
        list = list->next;
    }
    printf("\b\b\b\b\b     \n");
}

void LLDestructot(LinkedList **list) {
    while (*list) {
        LinkedList *next = (*list)->next;
        free(*list);
        *list = next;
    }
    printf("List is destructed now\n");
}

LinkedList *LLSearch(LinkedList *list, char c) {
    LinkedList *sent = list;
    while (list) {
        sent = list;
        if (list->c == c) return list;
        list = list->next;
    }
    return NULL;
}