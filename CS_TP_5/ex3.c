#include <stdio.h>

int main() {
	char boolean = 'f';
	int n, a;
	scanf("%d", &n);
	int arr[n];
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	scanf("%d", &a);
	
	int max = n;
	int min = 0;

	while (min <= max) {
		if (arr[(min+max)/2] > a)
			max = (min + max)/2 - 1;
		else if (arr[(min+max)/2] < a)
			min = (min + max)/2 + 1;
		else {
			boolean = 't';
			break;
		}
	}

	boolean == 't' ? printf("arr[%d] = %d", arr[(min + max) / 2 - 1], a) : printf("%d is not found in array", a);

	printf("\n");

	return 0;
}
