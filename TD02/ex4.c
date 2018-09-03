#include <stdio.h>

void printArray(int arr[], int nb);
void initialize(int arr[], int nb);
void input(int arr[], int nb);
void duplicate(int original[], int cpy[], int nb);
int belongs(int arr[], int nb, int searched);
int maximum(int arr[], int nb);
void reverse(int arr[], int rev[], int nb);
void permute(int arr[], int perm[], int nb);

int main () {
	int array[10] = {0, 2, 7, 8, 12, 354, -5, 1, 10, 9};
	int perm[10];
	permute(array, perm, 10);
	printArray(perm, 10);

	return 0;
}

void printArray (int arr[], int nb) {
	for (int i = 0; i < nb; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

void initialize(int arr[], int nb) {
	for (int i = 0; i < nb; i++)
		arr[i] = 0;
}

void input(int arr[], int nb) {
	for (int i = 0; i < nb; i++)
		scanf("%d ", &arr[i]);
}

void duplicate(int original[], int cpy[], int nb) {
	for (int i = 0; i < nb; i++)
		cpy[i] = original[i];
}

int belongs(int arr[], int nb, int searched) {
	for (int i = 0; i < nb; i++) if (arr[i] == searched) return 1;
	return 0;
}

int maximum(int arr[], int nb) {
	int max = arr[0];
	for (int i = 1; i < nb; i++) if (arr[i] > max) max = arr[i];
	return max;
}

void reverse(int arr[], int rev[], int nb) {
	for (int i = 0; i < nb; i++) rev[i] = arr[nb-i-1];
}

void permute(int arr[], int perm[], int nb) {
	for (int i = 0; i < nb; i++) {
		if (i + 1 == nb) perm [0] = arr[i];
		else perm [i+1] = arr[i]; 
	}
}



