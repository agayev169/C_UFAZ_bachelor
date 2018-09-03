#include <stdio.h>

short n;

int main() {
	printf("Choose the type of animals:\nMammal(1), Crocodile(2), Human(3), Bird(4), Fish(5)\n");
	scanf("%d", &n);
	switch (n) {
	case 1:
		printf("Human");
		break;
	case 2:
		printf("American crocodile, Freshwater crocodile, Gunay");
		break;
	case 3:
		printf("Allan Turing, You, Me");
		break;
	case 4:
		printf("Owl, Parrot");
		break;
	case 5:
		printf("Blowfish, Red lionfish");
		break;
	}
	printf("\n");
}
