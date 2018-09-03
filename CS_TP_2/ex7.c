#include <stdio.h>

int main() {
	float result = 1;
	int n;
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) result += (float)1/i;
	printf("%f\n", result);
}
