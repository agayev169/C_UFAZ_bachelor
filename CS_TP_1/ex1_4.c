#include <stdio.h>

int result = 0;

int main() {
	for (int i=1;i<=10;i++)
		result+=i;
	printf("The sum of first 10 inteers = %d\n",result);
}
