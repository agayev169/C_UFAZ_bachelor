#include <stdio.h>

int counter = 0, n, k;

int main () {
	scanf("%d", &n);
	int arr1[n];
	for (int i = 0; i < n; i++) scanf("%d", &arr1[i]);
	printf("\n");

	scanf("%d", &k);
	int arr2[k];
	for (int i = 0; i < k; i++) scanf("%d", &arr2[i]);
	printf("\n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (arr1[i] == arr2[j]) {
				if (k > n) arr1[i] = 0;
				else arr2[j] = 0;
				counter++;
			}
		}
	}


	if (k > n && counter >= n)
		printf("arr1[] is totally included inside arr2[]");
	else if (k <= n && counter >= k)
		printf("arr2[] is totally included inside arr1[]");
	else
		printf("arrays are not totally included inside each other");

	printf("\n");
	return 0;
}
