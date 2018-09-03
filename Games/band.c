#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
	srand(time(0));

	const int startingMoney = 500;
	const int turnCost = 50;
	const int doubleBonus = 60;
	const int tripleBonus = 100;

	int money = startingMoney;
	int panel0 = 0;
	int panel1 = 0;
	int panel2 = 0;

	do {
		system("clear");
		
		printf("\n\n");
		printf("\t ######### \n");
		printf("\t#         # \n");
		printf("\t########### \n");
		printf("\t#         # \n");
		printf("\t# %d  %d  %d # \n", panel0, panel1, panel2);
		printf("\t#         # \n");
		printf("\t########### \n");
		printf("\n");
		printf("\n");
		printf("Money: %d$", money);
		printf("\n");
		
		getchar(); 

		money -= turnCost;
		
		panel0 = 1 + rand() % 3;
		panel1 = 1 + rand() % 3;
		panel2 = 1 + rand() % 3;

		if (panel0 == panel1 && panel1 == panel2) money += tripleBonus;
		else if (panel0 == panel1 || panel1 == panel2 || panel0 == panel2) money += doubleBonus;

	} while (money >= turnCost);

	return 0;
}
