#include <stdio.h>

int main() {
	FILE *fp;
	fp = fopen("file.txt", "r");
	int num;
	
	if (fp == NULL)
			printf("ERROR");
	else {
		while (1) {
			if (feof(fp)) break;
			num = fgetc(fp);
			printf("%c", num);
		}
	fclose(fp);

	printf("\n");
	return 0;
}

/* fsanf(fp, "%d", &table[i]) == 1 */
