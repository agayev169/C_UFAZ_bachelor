#include <stdio.h>

int number, counter = 0;
long factorialRes;

long factorial(int arg);

int main() {
	scanf("%d",&number);
	factorialRes = factorial(number);
	for (int i=1;i<=factorialRes/2;i++) {
		if (factorialRes % i == 0) {
			counter++;
        }
	}
	printf("%d\n",counter+1);
}

long factorial(int arg) {
	long result = 1;
	for (int i=2;i<=arg;i++)
		result*=i;
	return result;
}
