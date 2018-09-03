#include <stdio.h>

long factorial(int number){
	if(number <=1)
		return 1;
	else
		return (number * factorial(number-1));
}

int main() {
	int i;
	for(i = 0; i <= 10; i++) printf("%2d! = %ld\n", i, factorial(i));
	return 0;
}
