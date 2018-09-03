#include <stdio.h>

int num;
long result = 1;

int main() {
    scanf("%d",&num);
	for (int i = 2; i <= num; i++)
		result *= i;
	printf("%d\n",result);
}
