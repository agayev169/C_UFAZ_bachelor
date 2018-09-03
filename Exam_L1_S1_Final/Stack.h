#include <stdio.h>
#include <stdlib.h>
//---------------1---------------
// In the first algorithm we need access only to the newest element - That is stack
//---------------2---------------
// In the second algorithm we need access only to the oldest element - That is queue
//---------------3---------------
//In the first algorithm it's better to use simply linked list since we don't know the number of elements at all
//In the second algorithm it's better to use array since we know that the maximum number of linked cells is 4 and we need the information only about these 4 cells
typedef struct LinkedList{
    int val;
    struct LinkedList *next;
} LinkedList;

typedef struct {
    LinkedList *list;
} Stack;

LinkedList *L_new(int value);

Stack S_new();

Stack S_push(Stack stack, int num);

Stack S_pop(Stack stack);

void S_showFor(Stack stack, char *label);
