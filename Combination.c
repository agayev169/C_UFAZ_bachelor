#include <stdio.h>

int number1,number2;

double factorial (int arg) {
	double result = 1;
	for (int i=2;i<=arg;i++)
		result*=i;
	return result;
}

int main () {
	scanf("%d%d",&number1,&number2);
	printf("%.0f",factorial(number1)/(factorial(number2)*factorial(number1 - number2)));
}
