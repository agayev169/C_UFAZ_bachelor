#include <stdio.h>

int dichotomy(int arr[], int n, int val) {
    int max = n;
    int min = 0;

    while (min <= max) {
        if (arr[(min+max)/2] > val)
            max = (min + max)/2 - 1;
        else if (arr[(min+max)/2] < val)
            min = (min + max)/2 + 1;
        else {
            return (min+max)/2;
        }
    }
    return -1;
}

int main() {
	int n, a;
    printf("Number of elements in a new array: ");
	scanf("%d", &n);
	int arr[n];
	for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Number to find: ");
	scanf("%d", &a);

    int ans = dichotomy(arr, n, a);
	ans == -1 ? printf("%d was not found in array\n", a) : printf("arr[%d] = %d\n", ans, a);

	return 0;
}
