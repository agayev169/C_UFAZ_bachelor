#include <stdio.h>
#include <stdlib.h>

float *TakeTable(int *NBelement) {
	int n;
	float *tab;
	printf("Enter the size of the table: ");
	scanf("%d", &n);
	*NBelement = n;
	tab = (float*)malloc(n*sizeof(float));
	printf("Enter the elements: ");
	for(int i = 0; i < n; i++) scanf("%f", &tab[i]);
	
	return tab;
}

void ShowTable(float *tab, int nb) {
	for (int i = 0; i < nb; i++) printf("%.2f\n", tab[i]);
}

int main() {
	int nb;
	float *tab;
	tab = TakeTable(&nb);
	ShowTable(tab, nb);

	free(tab);
	return 0;
}
