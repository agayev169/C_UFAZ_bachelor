#include <stdio.h>

typedef struct {
	int arr[4];
	int head;
	int tail;
	int size;
} Queue;

Queue enqueue (Queue q, int num);
Queue dequeue (Queue q);
int size(Queue q);
int tail(Queue q);
int head(Queue q);

int main() {
	Queue q;
	q.head = 0;
	q.tail = 0;
	q.size = 0;
	for (int i = 0; i < 4; i++) {
		q.arr[i] = 0;
	}

	printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));
	q = enqueue(q, 1);
		printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));
	q = enqueue(q, 2);
		printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));
	q = enqueue(q, 3);
		printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));
	q = enqueue(q, 4);
		printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));
	q = dequeue(q);
		printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));
	q = dequeue(q);
		printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));
	q = dequeue(q);
		printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));
	q = dequeue(q);
		printf("size : %d; tail : %d; head : %d\n", size(q), tail(q), head(q));

	/*for (int i = 0; i < size; ++i) {
		printf("arr[%d] = %d\n", i, q.arr[i]);
	}*/

	//q = enqueue(q, 5);
	//printf("head = %d, tail = %d, size = %d\n", q.arr[q.head], q.arr[q.tail+3], q.size);

	return 0;
}

Queue enqueue (Queue q, int num) {
	//printf("tail = %d\n", q.tail);
	if (q.tail == 4)
		q.arr[0] = num;
	else
		q.arr[q.tail] = num;
	q.tail = (++q.tail)%4;
	// printf("in function tail = %d\n", q.tail);
	// printf("in function head = %d\n", q.head);
	q.size++;
	return q;
}

Queue dequeue (Queue q) {
	q.head == 3 ? q.head -= 3 : q.head++;
	q.size--;
	return q;
}

int tail(Queue q) {
	return q.arr[q.tail];
}

int head(Queue q) {
	return q.arr[q.head];
}

int size(Queue q) {
	return q.size;
}
