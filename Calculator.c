#include <stdio.h>

int main() {
	int num1,num2,result;
	char operation;
	printf ("Please,write the operation(+ - * /): ");
	operation = getchar();
	printf ("Please,write 1st number: ");
	scanf("%d",&num1);
	printf ("Please,write 2nd number: ");
	scanf("%d",&num2);
	switch (operation) {
		case '+':printf("The result is %d\n",num1 + num2);
		break;
		case '-':printf("The result is %d\n",num1 - num2);
		break;	
		case '*':printf("The result is %d\n",num1 * num2);
		break;
		case '/':
		if (num2 == 0) {
			printf("Second number equals to 0. I can't divide something by 0\n");
		} else	
		printf("The result is %d\n",num1 / num2);
		break;
	}
	
	return 0;
}
