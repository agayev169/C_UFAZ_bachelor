#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int key, count = 1, bullets = 6;
enum status {true, false};

int main() {
	enum status win = false;
	srand(time(NULL));
	while (win == false) {
		printf("The move is %d's player\n",count);
		scanf("%d",&key);
		key = rand() % bullets;
		if (key == 0) {
			printf("%d player has been died :(\n",count);
			win = true;
		}
		else printf("You're lucky! :)\n");
		count++;
		if (count > 2) count/=2;
		bullets--;
	}
}
