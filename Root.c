#include <stdio.h>

float number;
double min = 0,max;

int main() {
	scanf("%f",&number);
	while (number <= 0) {
		scanf("%f",&number);
	}
	max = number;
	while ((min + max)/2 * (min + max)/2 > number + 0.0000000001 || (min + max)/2 * (min + max)/2 < number - 0.0000000001) {
	
		if ((min + max)/2 * (min + max)/2 > number) max = (min + max)/2;
		else if ((min + max)/2 * (min + max)/2 < number) min = (min + max)/2;
	}
	printf("Root of %f = %f\n",number,(min + max)/2);
}
