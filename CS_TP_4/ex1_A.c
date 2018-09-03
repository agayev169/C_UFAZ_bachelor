#include <stdio.h>

int main() {
	float u = 0;
	int n;
	scanf("%i",&n);
	for(int i = 0; i <= n; i++)
	{
		printf("u[%i] = %f\n", i, u);
		printf("f(u[%i]) - u[%i] = %f\n", i, i, -u*u + 0.5);
		u+=(0.5 - u*u);
	}
}
