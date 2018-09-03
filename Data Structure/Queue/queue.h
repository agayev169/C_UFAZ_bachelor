#include <stdio.h>
#include <stdlib.h>

typedef struct Fifo {
    int enqueue;
    int dequeue;
    int size;
    int *fifo;
} Fifo;

int createFifo(Fifo *p, int n);
int enqueue(Fifo *p, int n);
int dequeue(Fifo *p);
int destroy(Fifo *p);
int expand(Fifo *p);
int compress(Fifo *p);
int printQueue(Fifo p);
int printAll(Fifo p);
