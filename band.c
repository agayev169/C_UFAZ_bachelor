#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main () {
	const int startingMoney = 500;
	const int turnCost = 50;
	const int doubleBonus = 60;
	const int tripleBonus = 100;

	int money = startingMoney;
	char panel0 = 'X';
	char panel1 = 'X';
	char panel2 = 'X';

	do {
		system("clear");
		
		printf("\n\n");
		printf("\t ######### \n");
		printf("\t#         # \n");
		printf("\t########### \n");
		printf("\t#         # \n");
		printf("\t# %c  %c  %c # \n", panel0, panel1, panel2);
		printf("\t#         # \n");
		printf("\t########### \n");
		printf("\n");

		_getch();
	} while (money >= turnCost);

	return 0;
}
