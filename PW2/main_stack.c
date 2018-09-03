#include <stdio.h>
#include "stack.h"

int main()
{
	Stack stack = ST_new();

	stack = ST_push(stack, 1);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_push(stack, 5);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_push(stack, 2);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_push(stack, 7);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_pop(stack);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_pop(stack);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_pop(stack);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_push(stack, 3);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_push(stack, 10);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_pop(stack);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_pop(stack);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));
	stack = ST_pop(stack);
	printf("Size of the stack is %d\n", ST_size(stack));
	printf("The top of the stack is %d\n", ST_top(stack));

	return 0;
}