#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(short table[9][9]);
void print(short table[9][9]);

int main() {
	short table[9][9] = {{1,2,3,4,5,6,7,8,9},{4,5,6,7,8,9,1,2,3},{7,8,9,1,2,3,4,5,6},{2,3,4,5,6,7,8,9,1},{5,6,7,8,9,1,2,3,4},{8,9,1,2,3,4,5,6,7},{3,4,5,6,7,8,9,1,2},{6,7,8,9,1,2,3,4,5},{9,1,2,3,4,5,6,7,8}};

	shuffle(table);
	print(table);

	return 0;
}

void shuffle(short table[9][9]) {
	srand(time(NULL));
	for (int i = 0; i < 5000; i++) {
		short x1 = rand()%3;
		short x2 = rand()%3;
		while(x2 == x1)x2 = rand()%3;
		for (int j = 0; j < 9; j++) {
			short hold = table[x1][j];
			table[x1][j] = table[x2][j];
			table[x2][j] = hold;
		}
		x1 = rand()%3;
		x2 = rand()%3;
		while(x2 == x1)x2 = rand()%3;
		for (int j = 0; j < 9; j++) {
			short hold = table[j][x1];
			table[j][x1] = table[j][x2];
			table[j][x2] = hold;
		}
		x1 = rand()%3 + 3;
		x2 = rand()%3 + 3;
		while(x2 == x1)x2 = rand()%3 + 3;
		for (int j = 0; j < 9; j++) {
			short hold = table[x1][j];
			table[x1][j] = table[x2][j];
			table[x2][j] = hold;
		}
		x1 = rand()%3 + 3;
		x2 = rand()%3 + 3;
		while(x2 == x1)x2 = rand()%3 + 3;
		for (int j = 0; j < 9; j++) {
			short hold = table[j][x1];
			table[j][x1] = table[j][x2];
			table[j][x2] = hold;
		}
		x1 = rand()%3 + 6;
		x2 = rand()%3 + 6;
		while(x2 == x1)x2 = rand()%3 + 6;
		for (int j = 0; j < 9; j++) {
			short hold = table[x1][j];
			table[x1][j] = table[x2][j];
			table[x2][j] = hold;
		}
		x1 = rand()%3 + 6;
		x2 = rand()%3 + 6;
		while(x2 == x1)x2 = rand()%3 + 6;
		for (int j = 0; j < 9; j++) {
			short hold = table[j][x1];
			table[j][x1] = table[j][x2];
			table[j][x2] = hold;
		}
	}
}

void print(short table[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			j % 3 == 2 ? printf("%hi ", table[i][j]) : printf("%hi", table[i][j]);
		}
		printf("\n");
		if(i % 3 == 2) printf("\n");
	}
}
