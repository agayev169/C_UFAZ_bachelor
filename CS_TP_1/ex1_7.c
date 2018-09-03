#include <stdio.h>

int number,result=0,counter=0;

int main() {
	printf("Your numbers: ");
	while (scanf("%d",&number) != EOF) {
		if (number % 2 == 0)
			result+=number;
	}
	printf("The sum = %d\n",result);
}
