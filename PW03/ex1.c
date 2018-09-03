#include <stdio.h>

int divide (float a, float b, float *q);

int main() {
	float a, b, q;
	a = 365;
	b = 5;
	int divided = divide (a, b, &q);
	printf("%f\n", q);

	return 0;
}

int divide (float a, float b, float *q) {
	if (b == 0) return 0;
	printf("%f %f\n", a, b);
	*q = a/b;
	printf("%f\n", *q);
	return 1;
}