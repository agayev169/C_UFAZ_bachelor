#include <stdio.h>
#include "stack.h"

int main()
{
	Stack stack = ST_new();

	stack = ST_push(stack, 1);
	ST_size(stack);
	ST_top(stack);
	stack = ST_push(stack, 5);
	ST_size(stack);
	ST_top(stack);
	stack = ST_push(stack, 2);
	ST_size(stack);
	ST_top(stack);
	stack = ST_push(stack, 7);
	ST_size(stack);
	ST_top(stack);
	stack = ST_pop(stack);
	ST_size(stack);
	ST_top(stack);
	stack = ST_pop(stack);
	ST_size(stack);
	ST_top(stack);
	stack = ST_pop(stack);
	ST_size(stack);
	ST_top(stack);
	stack = ST_push(stack, 3);
	ST_size(stack);
	ST_top(stack);
	stack = ST_push(stack, 10);
	ST_size(stack);
	ST_top(stack);
	stack = ST_pop(stack);
	ST_size(stack);
	ST_top(stack);
	stack = ST_pop(stack);
	ST_size(stack);
	ST_top(stack);
	stack = ST_pop(stack);
	ST_size(stack);
	ST_top(stack);

	return 0;
}