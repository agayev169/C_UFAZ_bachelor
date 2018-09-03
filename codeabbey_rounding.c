#include <stdio.h>

int n,num1,num2;

int main() {
	scanf("%d",&n);
	int arr[n];
	for (int i = 0;i < n;i++) {
		scanf("%d%d",&num1,&num2);
		if (num1 / num2 >= 0 && num1 > 0 && num2 > 0 && num1 % num2 >= num2 / 2 || num1 / num2 >= 0 && num1 < 0 && num2 < 0 && num1 % num2 >= -num2 / 2) arr[i] = num1 / num2 + 1;
		else if (num1 / num2 <= 0 && num1 < 0 && num2 > 0 && -num1 % num2 >= num2 / 2 || num1 / num2 <= 0 && num2 < 0 && num1 > 0 && num1 % num2 >= -num2 / 2) arr[i] = num1 / num2 - 1;
		else arr[i] = num1 / num2;
	}
	for (int i = 0; i < n;i++) printf("%d ",arr[i]);
	printf("\n");
}
