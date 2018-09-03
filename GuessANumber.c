#include <stdio.h>

int main() {
	printf("Guess a number I have imagined between 0 and 100\n");
	srand(time(NULL));
	int number = rand()%100+1;
	int userNumber;
	while (number != userNumber) {
		scanf("%d",&userNumber);
		if (number > userNumber)
			printf ("Your number is smaller than guessed one\n");
		if (number < userNumber)
			printf ("Your number is greater than guessed one\n");
	}
	printf ("You have won :)\n");
}
