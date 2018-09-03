#include <stdio.h>

float number;
double sin = 0;

double power (double arg, int pow) {
	double result = 1;
	for (int i = 0; i < pow; i++) 
		result*=arg;
	return result;
}

double factorial (double arg) {
	double result = 1;
	for (int i = 2; i <= arg; i++)
		result*=i;
	return result;
}

int main() {
	scanf("%f",&number);
	for (int i = 1; i < 100; i++) {
		sin+=(power(-1,i-1)*power(number/57.2957796,2*i-1))/factorial(2*i-1);
	}
	printf("sin %f = %f\n",number,sin);
}
