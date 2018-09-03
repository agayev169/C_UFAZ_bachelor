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
			printf("code 1");
			break;
		case 2:
			printf("code 2");
			break;
		}
		break;
	case 2:
		printf("Choose the type of animals:\nHuman(1), Wings?(2)\n");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("code 3");
			break;
		case 2:
			printf("Bird(1), Fish(2)");
			scanf("%d", &n);
			switch (n) {
			case 1:
				printf("code 4");
				break;
			case 2:
				printf("code 5");
				break;
			}
			break;
		}
		break;
	}
	printf("\n");
}
