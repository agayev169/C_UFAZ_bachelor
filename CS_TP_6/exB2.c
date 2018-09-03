#include <stdio.h>

int main() {
	FILE *fp;

	fp = fopen("file.txt", "r");
	if(fp == NULL) printf("ERROR");
	fclose(fp);
}
