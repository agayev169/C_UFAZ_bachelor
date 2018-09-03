#include <stdio.h>

void checking(int a) {
	a % 2 == 0 ? printf("%d is even\n", a) : printf("%d is odd\n", a);
}

void prime_checking() {
	int boolean = 1;
	int n;
	scanf("%d", &n);
	for (int i = 2; i <= n/2; i++) {
		if(n % i == 0) boolean = 0;
	}
	printf("%d\n", boolean);
}

int main() {
	int a,b;

	scanf("%d%d", &a, &b);
	printf("%d / %d = %d\n", a, b, a/b);
	printf("Remainder of division %d by %d = %d\n", a, b, a%b);

	checking(a);
	checking(b);

	prime_checking();

	char *ptr, *ptr2;
	scanf("%s", ptr);
	int i = 0;
	while(*(ptr + i) != '\0')
		i++;
	int j = 0;
	while(ptr + i - j + 1 != ptr) {
		printf("%c", *(ptr + i - j));
		j++;
	}
	printf("\n");
	return 0;
}
