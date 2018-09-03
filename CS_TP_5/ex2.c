#include <stdio.h>

int main() {
	int n;
	scanf("%d", &n);
	int arr[n];
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
	for (int i = 0; i < n; i++) printf("%d ", arr[i]);
	printf("\n");
	
	for(int i = 1; i < n; i++) {
		int j = i - 1;
		int k = i;
		for(int j = i - 1; j >= 0 && arr[k] < arr [j]; j-- && k--) {
			arr[k] += arr[j];
			arr[j] = arr[k] - arr[j];
			arr[k] -= arr[j];
		}
	}
	for (int i = 0; i < n; i++) printf("%d ", arr[i]);

	printf("\n");

	return 0;
}
