#include <stdio.h>
#include "Stack.h"

LinkedList *L_new(int value) {
    LinkedList *l = (LinkedList*)calloc(1, sizeof(LinkedList));
    l->val = value;
    l->next = NULL;
    return l;
}

Stack S_new() {
    Stack s;
    s.list = NULL;
    return s;
}

Stack S_push(Stack stack, int num) {
	LinkedList *l = L_new(num);
    l->next = stack.list;
    stack.list = l;
	return stack;
}

Stack S_pop(Stack stack) {
	stack.list = stack.list->next;
	return stack;
}

int S_get(Stack stack) {
    return stack.list->val;
}

void S_showFor(Stack stack, char *label) {
	printf ("-----------------%s-----------------\n", label);
	for (LinkedList *i = stack.list; i != NULL; i = i->next)
		printf ("%p %d %p\n", i, i->val, i->next);
}
