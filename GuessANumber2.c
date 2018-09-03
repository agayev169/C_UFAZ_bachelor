#include <stdio.h>

int min = 0;
int max = 100;
short oper;

int main() {
	printf("Imagine a number between 1 and 100 and I will try to guess it\n");
	printf("Write 1 if my number is less than your number\n");
	printf("Write 2 if my number equals to your number\n");
	printf("Write 3 if my number is greater than your number\n");
	printf("%d\n",(min + max)/2);
	while (oper != 2) {
		scanf("%d",&oper);
		switch (oper) {
			case 1:
				min = (min + max)/2;
				break;
			case 3:
				max = (min + max)/2;
				break;
		}
		printf("%d\n",(min + max)/2);
	}
	printf("I've done it! :)\n");
}
