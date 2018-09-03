#include <stdio.h>

int main() {
	FILE *fpr, *fpr2, *fpw;
	fpr = fopen("first.txt", "r");
	fpr2 = fopen("final2.txt", "r");
	fpw = fopen("second.txt", "w");
	for (int i = 0; i < 110; i++) {
		fgetc(fpr) == fgetc(fpr2) ? fprintf(fpw, "0") : fprintf(fpw, "1");
		if (i % 10 == 9) fprintf(fpw, "\n");
	}
	fclose(fpr);
	fclose(fpr2);
	fclose(fpw);
	return 0;
}
