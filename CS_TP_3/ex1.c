#include <stdio.h>

short n;

int main() {
	printf("Choose the type of animals:\nMammal(1), Crocodile(2), Human(3), Bird(4), Fish(5)\n");
	scanf("%d", &n);
	switch (n) {
	case 1:
		printf("code 1");
		break;
	case 2:
		printf("code 2");
		break;
	case 3:
		printf("code 3");
		break;
	case 4:
		printf("code 4");
		break;
	case 5:
		printf("code 5");
		break;
	}
	printf("\n");
}
