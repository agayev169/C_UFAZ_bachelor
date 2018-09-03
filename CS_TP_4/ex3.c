#include <stdio.h>
#include <math.h>

int f(int i, int j) {
	if ((sqrt((i - 10) * (i - 10) + (j - 25)*(j - 25)/5) <= 8)) return 1;
	else return 0;
}

int j;
int i;

int main() {
	for (i = 1; i <= 20; i++) {
		for (j = 1; j <= 50; j++) {
			if (f(i ,j)) printf("*");
		else printf(" ");
		}
		printf("\n");
	}
}
