#include <stdio.h>
#include <stdlib.h>

void ReturnTable(int *arr, int n) {
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
}

void ReadingTable(int *arr, int n, FILE *fPtr) {
	for (int i = 0; i < n; i++)
		fscanf(fPtr, "%d", &arr[i]);
}

void RegisterTable(int *n, int *arr, FILE *fPtr) {
	fscanf(fPtr, "%d", n);
	arr = (int*)malloc(*n * sizeof(int)); 
}

FILE *OpenFile(char *f, FILE *fPtr) {
	return fopen(f, "r");
}

int main() {
	FILE *fPtr;
	char *f = "int.txt";
	fPtr = OpenFile(f, fPtr);

	int *arr;
	int n;
	RegisterTable(&n, arr, fPtr); 

	ReadingTable(arr, n, fPtr);
	
	ReturnTable(arr, n);

	printf("\n");
	return 0;
}
