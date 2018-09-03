#include <stdio.h>


void f(int *arr, int size) {
	// for (int i = 0; i <= size; ++i) {
	// 	arr[i] = 5;
	// }
	arr[-1] = 5; 
}

int main () {
int arr[10];
int N=10;
	printf("%p %p\n", arr-1, &N);
	f(arr, 10);
	printf("%d\n", N);

	return 0;
}