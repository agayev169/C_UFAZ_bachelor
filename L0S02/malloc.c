#include <stdio.h>
#include <stdlib.h>

int main() {
    int nums[5];
    int *nums2;

    int n;
    scanf("%d", &n);

    nums2 = malloc(n * sizeof(int));
    // nums2 = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("%d ", nums2[i]);
    }
    // nums2 = realloc(nums2, n + 5);

    FILE *fp = fopen("name.txt.", "r");//opened 
    int x;
    fread(&x, 1, sizeof(int), fp);

    fread(nums2, n, sizeof(int), fp);

    return 0;
}