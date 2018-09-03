#include <stdio.h>
#include "stack.h"
#define N 100

Stack ST_new() {
	Stack stack;
	stack.size = 0;
	return stack;
}

void ST_print (Stack stack) {
	for (int i = 0; i < stack.size; ++i)
		printf("%d\n", stack.st[i]);
}

int ST_size (Stack stack) {
	return stack.size;
}

Stack ST_push (Stack stack, int num) {
	if (stack.size == N) 
		printf("Error! The stack has already %d elements\n", N);
	else {
		stack.st[stack.size] = num;
		stack.size++;
	}
	return stack;
}

Stack ST_pop (Stack stack) {
	if (stack.size == 0) 
		printf("Error! The stack has already no elements\n");
	else {
		stack.st[stack.size-1] = 0;
		stack.size--;
	}
	return stack;
}

int ST_top (Stack stack) {
	if (stack.size == 0) {
		printf("Error! The stack has no elements\n");
		return -1;
	}
	return stack.st[stack.size-1];
}