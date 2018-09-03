#ifndef STACK
#define STACK

#define N 100

typedef struct {
	int st[N];
	int size;
} Stack;

Stack ST_new();
void ST_print (Stack stack);
int ST_size (Stack stack);
Stack ST_push (Stack stack, int num);
Stack ST_pop (Stack stack);
int ST_top (Stack stack);

#endif