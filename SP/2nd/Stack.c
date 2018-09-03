#include "Stack.h"

Stack ST_new(int nb_max)
{
	Stack ans=(Stack)malloc(sizeof(StructStack)); // A block of memory is allocated to store stack "ans".
	ans->_max_size=nb_max; // Maximum possible size of the stack is set to the given "nb_max".
	ans->_array=(Cell*)calloc(ans->_max_size, sizeof(Cell)); // A block of memory is allocated fot the array of "nb_max" elements of stack.
	ans->_first_free_place=0; // First free place index is set to 0.
	return ans; // The stack "ans" is returned.
}

void ST_free(Stack s)
{
	free(s->_array); // The block of memory containing the elements of the stack "s" is freed.
	free(s); // The block of memory containing the stack is freed.
}

void ST_check(Stack s, char *label)
{
	for(int i=0; i<s->_first_free_place; i++) // For each element of stack "s":
		CL_check(s->_array[i], label); // Output that element with a label "label".
}

unsigned char ST_isEmpty(Stack s)
{
	if(s->_first_free_place==0) // If the first free place of stack "s" is its 1th (a.k.a. 0th) place:
		return 1; // 1 is returned.
	return 0; // 0 is returned as default.
}

unsigned char ST_isFull(Stack s)
{
	if(s->_first_free_place==s->_max_size) // If the first free place index of stack "s" has reached the maximum size of the stack:
		return 1; // 1 is returned.
	return 0; // 0 is returned as default.
}

Stack ST_push(Stack s, Cell c)
{
	if(!ST_isFull(s)) {
		s->_array[s->_first_free_place]=c; // The element with index of the first free place of stack "s" is given a value of cell "c".
		s->_first_free_place++; // First free place index is incremented by one.
	}
	else
		printf("Error! There is no more place in stack\n");
	return s; // The resulting stack is returned.
}

Stack ST_pop(Stack s)
{
	if (!ST_isEmpty(s))
		s->_first_free_place--; // The first free place index is decremented by one, so that later a new element can be pushed to that element.
	else
		printf("Error! The list is already empty. Cannot pop\n");
	return s; // The resulting stack is returned.
}

void ST_top(Stack s, Cell *c)
{
	*c=s->_array[s->_first_free_place-1]; // The cell "c" is given the value of the element at the last not free place.
}

int ST_size(Stack s)
{
	return s->_first_free_place; // The index of the first free place is returned.
}

int ST_export(Stack s, Cell *solution)
{
	for(int i=0; i<s->_first_free_place; i++) // For each element of stack "s":
		solution[i]=s->_array[i]; // The value of that element is given to the corresponding element of "solution".
	return s->_first_free_place; // The number of elements of stack "s" is returned.
}
