#include <stdio.h>

void convert (int n, int x);

int main() {
	int n;
	printf("Number = ");
	scanf("%d", &n);

	int x;
	printf("X = ");
	scanf("%d", &x);
	convert(n, x);

	printf("\n");

	return 0;
}

void convert (int n, int x) {
	int ans, mod;

	ans = n / x;
	mod = n % x;
	if (n <= 0) return;
	convert(ans, x);
	printf("%d", mod);
}
