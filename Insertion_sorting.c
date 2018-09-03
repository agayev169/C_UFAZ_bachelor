#include <stdio.h>
#include <time.h>

int array[100], key;

int main() {
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
		array[i] = rand() % 1000;
	int key = array[0];
	for (int i = 1; i < 100; i++) {
		while (array[i] < array[i-1] && i > 0) {
			key = array[i];
			array[i] = array[i-1];
			array[i-1] = key;
			i--;
		}
	}
	for (int i = 0; i < 100; i++)
		printf("%4d",array[i]);
}
