#include <stdio.h>
#include <math.h>

int x, y, result = 1;

int main() {
	scanf("%i%i", &x, &y);
	for (int i = 1; i <= y; i++) result *= x;
	printf("x^y = %d\n", result);
}
