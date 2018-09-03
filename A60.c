#include <stdio.h>

int number;

double factorial (int arg) {
	double result = 1;
	for (int i=2;i<=arg;i++)
		result*=i;
	return result;
}

int main () {
	scanf("%d",&number);
	printf("%.0f\n",factorial(number)/factorial(number-3));
}
