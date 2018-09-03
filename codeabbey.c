#include <stdio.h>

int main() {
	int n;
	char c;
	scanf("%d", &n);
	char string[n][100];
	for (int i = 0; i < n; i++) {
		int j = 0;
		while ((c = getchar())!='\n' && j < 99) {
			string[i][j];
			j++;
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%s", string[i]);
	}
	
	printf("\n");
	return 0;
}
