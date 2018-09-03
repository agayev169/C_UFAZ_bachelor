#include <stdio.h>

void printArray(const int a[][3]) {
	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 2; j++) printf("%2d", a[i][j]);
		printf("\n");
	}
	printf("\n");
}

int main() {
	int a1[2][3] = {{1, 2, 3}, {4, 5, 6}};
	int a2[2][3] = {1, 2, 3, 4, 5};
	int a3[2][3] = {{1, 2}, {4}};

	printArray(a1);
	printArray(a2);
	printArray(a3);

	return 0;
}
