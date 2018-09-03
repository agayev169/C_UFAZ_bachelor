#include <stdio.h>

int main() {
	FILE *fpr, *fpr2, *fpw;
	fpr = fopen("first.txt", "r");
	fpw = fopen("final.txt", "w");
	fpr2 = fopen("second.txt", "r");
	for (int i = 0; i < 110; i++) {
		fgetc(fpr) == fgetc(fpr2) ? fprintf(fpw, " ") : fprintf(fpw, "*");
		if (i % 10 == 9) fprintf(fpw, "\n");
	}
	fclose(fpr);
	fclose(fpr2);
	fclose(fpw);
	return 0;
}
