#include <stdio.h>

int number=0,sum=0,counter=0;
float average;

int main() {
	printf("Enter numbers and I'll calculate their average.\n-1 to stop entering numbers\n");
	scanf("%d",&number);
	while (number!=-1) {
		sum+=number;
		scanf("%d",&number);
		counter++;
	}
	average = sum / counter;
	printf("The average of entered numbers = %f\n",average);
}
