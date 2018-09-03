#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int _size;
	int *_array;
} Stack;

Stack ST_new (int maxsize);

int main() {
	Stack myStack;
	myStack = ST_new(10);

	return 0;
}

Stack ST_new (int maxsize) {
	Stack temp;
	temp._array = (int*)calloc(maxsize, sizeof(int));
	return temp;
}