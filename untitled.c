#include <stdio.h>

struct intList {
	int value;
	struct intList *next;
};

int main() {
	struct intList *list;
	list = (struct intList*) calloc(2, sizeof(struct intList));
	list->value = 5;
	list->next = list[1];
	list[1].value = 20;
	list[1].next = NULL;
}