#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct LinkedList {
    int val;
    char c;
    struct LinkedList *next;
} LinkedList;

void LLAdd(LinkedList **list, int val, char c);
void LLPrint(LinkedList *list);
void LLDestructot(LinkedList **list);
LinkedList *LLSearch(LinkedList *list, char c);

#endif