#include <stdio.h>

typedef struct {
	int arr[4];
	int max;
	int first;
	int size;
}Queue;

int nextIndex(int ind, int max);
Queue QU_new();
int QU_size(Queue q);
int QU_isEmpty(Queue q);
Queue QU_enqueue(Queue q, int n);
void QU_Show(Queue q);
Queue QU_dequeue(Queue q);
int QU_head(Queue q);

int main() {
	Queue q = QU_new();
	q = QU_enqueue(q, 1);
	QU_Show(q);
	q = QU_enqueue(q, 5);
	QU_Show(q);
	q = QU_enqueue(q, 2);
	QU_Show(q);
	q = QU_enqueue(q, 7);
	QU_Show(q);
	q = QU_dequeue(q);
	QU_Show(q);
	q = QU_dequeue(q);
	QU_Show(q);
	q = QU_dequeue(q);
	QU_Show(q);
	q = QU_enqueue(q, 3);
	QU_Show(q);
	q = QU_enqueue(q, 10);
	QU_Show(q);
	q = QU_dequeue(q);
	QU_Show(q);
	q = QU_dequeue(q);
	QU_Show(q);
	q = QU_dequeue(q);
	QU_Show(q);

	return 0;
}

int nextIndex(int ind, int max) {
  return ((ind+1)%max);
}

Queue QU_new() {
	Queue q;
	q.size=0;
	q.max=4;
	q.first=0;
	return q;
}

int QU_size(Queue q) {
	return q.size;
}

int QU_isEmpty(Queue q) {
	if(q.size == 0) return 1;
	return 0;
}

Queue QU_enqueue(Queue q, int n) {
	if (QU_size(q) >= q.max) {
		printf("Error! The queue already has %d elements\n", q.max);
		return q;
	}
	q.arr[(q.first+q.size)%4] = n;
	q.size++;
	return q;
}

Queue QU_dequeue(Queue q) {
	if (!QU_isEmpty(q)) {
		q.first = (q.first+1)%4;
		q.size--;
		return q;
	}
	printf("Error! There is no element in queue. Cannot dequeue\n");
	return q;
}

void QU_Show(Queue q) {
	if (!QU_isEmpty(q)) {
		printf("Head : %d,Head_val : %d, Tail : %d, Tail_val : %d, Size : %d\n", q.first, q.arr[q.first], (q.first+q.size-1)%4, q.arr[(q.first+q.size-1)%4], QU_size(q));
		return;
	}
	printf("Error! Queue is empty. Cannot show it\n");
}

int QU_head(Queue q) {
	if (!QU_isEmpty(q))
		return q.arr[q.first];
	printf("Error! The list is empty. Cannot return head\n");
	return 0;
}
