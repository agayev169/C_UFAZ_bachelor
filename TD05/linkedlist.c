#include <stdio.h>
#include <stdlib.h>

struct intList {
	int value;
	struct intList *next;
};

struct floatList {
	float value;
	struct floatList *next;
};

struct charList {
	char value;
	struct charList *next;
};

struct int5ArrayList {
	int value[5];
	struct int5ArrayList *next[5];
};

struct intArrayList {
	int *value;
	struct intArrayList **next;
};

struct color {
	unsigned char red, green, blue;
};

struct colorList {
	struct color value;
	struct colorList *next;
};

struct floatList *FL_new1(float x);
void FL_show1(struct floatList *f, char *label);
void FL_show(struct floatList *list, char *label);
void FL_showFor(struct floatList *f, char *label);

int main() {
	struct floatList *f1, *f2, *f3;
	f1 = FL_new1(3.1415926);
	f2 = FL_new1(2.718281828);
	f3 = FL_new1(9.81);

	f2->next = f3;
	f1->next = f2;

	FL_show1(f1, "first");
	FL_show1(f2, "second");
	FL_show1(f3, "third");

	printf("\n");

	FL_showFor(f1, "first");
	FL_showFor(f2, "second");
	FL_showFor(f3, "third");

	return 0;
}

struct floatList *FL_new1(float x) {
	struct floatList *floats = (struct floatList*)calloc(1, sizeof(struct floatList));
	floats->value = x;
	floats->next = NULL;
	return floats;
}

void FL_show1(struct floatList *f, char *label) {
	printf ("%10s : %p %f %p\n", label, f, f->value, f->next);
}

void FL_show(struct floatList *f, char *label) {
	printf ("-----------------%s-----------------\n", label);
	do {
		FL_show1(f, label);
		f = f->next;
	} while (f != NULL);
}

void FL_showFor(struct floatList *f, char *label) {
	printf ("-----------------%s-----------------\n", label);
	for (struct floatList *i = f; i != NULL; i = i->next)
		FL_show1(f, label);
}