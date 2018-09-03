#include <stdio.h>

float euro;

int main() {
	printf("How many euros do you have? "); 
	scanf("%f",&euro);
	printf("You have %.2f manats\n",euro * 1.9445);
}
