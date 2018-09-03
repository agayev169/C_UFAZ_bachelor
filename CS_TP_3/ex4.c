#include <stdio.h>

short n;

int main() {
	printf("Choose the type of animals:\nBreastfeeding?(1), Talk?(2)\n");
	scanf("%d", &n);
	switch (n) {
	case 1:
		printf("Choose the type of animals:\nMammal(1), Crocodile(2)\n");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("Human");
			break;
		case 2:
			printf("American crocodile, Freshwater crocodile, Gunay");
			break;
		}
		break;
	case 2:
		printf("Choose the type of animals:\nHuman(1), Wings?(2)\n");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("Allan Turing, You, Me");
			break;
		case 2:
			printf("Bird(1), Fish(2)");
			scanf("%d", &n);
			switch (n) {
			case 1:
				printf("Owl, Parrot");
				break;
			case 2:
				printf("Blowfish, Red lionfish");
				break;
			}
			break;
		}
		break;
	}
	printf("\n");
}
