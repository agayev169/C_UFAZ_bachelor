#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int card_num;

char *get_card() {
	char *card;
	card_num = rand() % 11 + 1;
	switch(card_num) {
	case 1:
		*card = '1';
		break;
	case 2:
		*card = '2';
		break;
	case 3:
		*card = '3';
		break;
	case 4:
		*card = '4';
		break;
	case 5:
		*card = '5';
		break;
	case 6:
		*card = '6';
		break;
	case 7:
		*card = '7';
		break;
	case 8:
		*card = '8';
		break;
	case 9:
		*card = '9';
		break;
	case 10:
		*card = "10";
		card_num = rand() % 4;
		if (card_num == 0) *card = "10";
		else if (card_num == 1) *card = "J";
		else if (card_num == 2) *card = "Q";
		else if (card_num == 3) *card = "K";
		break;
	case 11:
		*card = 'A';
		break;
	}
	return card;
}

int main() {
	srand(time(NULL));
	char *player[2];	
	char *dealer[2];

	

	player[0] = get_card();
	player[1] = get_card();
	dealer[0] = get_card();
	dealer[1] = get_card();
	
	printf("Player's cards: ");
	for(int i = 0; player[i] != '\0'; i++)
		printf("%s ", player[i]);
	printf("\nDealer's card: ");
	printf("%s ", dealer[0]);


	printf("\n");
	return 0;
}
