#include <stdio.h>

void callByValue(int num1, int num2);
void callByReference(int *num1, int *num2);

int main() {
	int num1, num2;

	printf("num1 = ");
	scanf("%d", &num1);
	
	printf("num2 = ");
	scanf("%d", &num2);

	callByValue(num1, num2);

	printf("After calling by value:\nnum1 = %d\tnum2 = %d\n", num1, num2);

	callByReference(&num1, &num2);

	printf("After calling by reference:\nnum1 = %d\tnum2 = %d", num1, num2);

	printf("\n");
	return 0;
}

void callByValue(int num1, int num2) {
	num1 += num2;
	num2 = num1 - num2;
	num1 -= num2;
	printf("num1 inside callByValue = %d\nnum2 inside callByValue = %d\n", num1, num2);
}

void callByReference(int *num1, int *num2) {
	*num1 += *num2;
	*num2 = *num1 - *num2;
	*num1 -= *num2;
	printf("num1 inside callByValue = %d\nnum2 inside callByValue = %d\n", *num1, *num2);
}
