#include <stdio.h>

int main() {
	int x, y, result = 0;
	scanf("%d%d", &x, &y);
	for (int i = 0; i < y; i++) result += x;
	printf("x * y = %d\n", result);
}
