#include <stdio.h>

int counter = 0;

int main() {
	char boolean = 'n';
	int n, k;
	scanf("%d", &n);
	int arr1[n],arr2[k];
	for (int i = 0; i < n; i++) scanf("%d", &arr1[i]);
	printf("\n");
	scanf("%d", &k);
	for (int i = 0; i < k; i++) scanf("%d", &arr2[i]);
	printf("\n");

	int min = 0;
	int max = n;

	for (int j = 0; j < k; j++) {
		for (int min = 0,max = n; min <= max;) {
			if (arr1[(min+max)/2] > arr2[j])
				max = (min + max)/2 - 1;
			else if (arr1[(min+max)/2] < arr2[j])
				min = (min + max)/2 + 1;
			else {
				counter++;
				break;
			}
		}
	}

	if (counter == 0) printf("There is no intersection");
	else printf("There is intersection");

	printf("\n");

	return 0;
}
