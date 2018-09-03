#include <stdio.h>

int a, j;

int main() {
	scanf("%d%d", &a, &j);
	float x[j];
	x[0] = a;
	for (int i = 1; i < j; i++) 
		x[i] = (x[i-1] + a/x[i-1]) / 2;
	printf("The square root of %d with precision %d = %f\n", a, j, x[j-1]);
}
