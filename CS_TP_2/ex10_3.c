#include <stdio.h>

int j;
float a;

int main() {
	scanf("%f%d", &a, &j);
	while (j >= 50) {
		printf("J must be less than 50\n");
		scanf("%d", &j);
	}
	float x[j];
	x[0] = a;
	for (int i = 1; i < j; i++) {
		x[i] = (x[i-1] + a/x[i-1]) / 2;
		printf("The square root of %f with precision %d = %f\n", a, i+1
, x[i]);
	}
}
