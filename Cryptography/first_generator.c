#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	FILE *fp;
	int n;
	srand(time(NULL));
	fp = fopen("first.txt", "w");
	for (int i = 0; i < 110; i++) {
		n = rand()%2;
		fprintf(fp, "%d", n);
		if (i % 10 == 9) fprintf(fp, "\n");
	}
	fclose(fp);
	return 0;
}
