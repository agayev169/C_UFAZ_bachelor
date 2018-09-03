#include <stdio.h>
#include <math.h>

float func(float x) {
	return ((2*x*x*x+3)*(x*x-1)/(sqrt(3*x*x+1)));
}

float func2(float x, float h) {
	return ((func(x+h)- func(x-h))/2*h);
}

float func3(float x, float h) {
	return ((func2(x+h, h)- func2(x-h, h))/2*h);
}

int main() {
	int fprime;
	printf("1 for f\n2 for f'\n3 for f''\n");
	scanf("%d", &fprime);
	while (fprime < 1 || fprime > 3)
		scanf("%d", &fprime);
	float x;
	printf("X = ");
	scanf("%f", &x);
	float f;
	if (fprime == 1) {
		f = func(x);
		printf("f(%f) = %f\n", x, f);
	}
	else if (fprime == 2) {
		float h;
		printf("h = ");
		scanf("%f", &h);
		f = func2(x, h);
		printf("f'(%f) = %f\n", x, f);
	} else {
		float h;
		printf("h = ");
		scanf("%f", &h);
		f = func3(x, h);
		printf("f''(%f) = %f\n", x, f);
	}	
}
