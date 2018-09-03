#include <stdio.h>

long int powOfTwo(int x) {
    long int res = 0;
    for (int i = 0; i < x; i++) {
        res *= 2;
    }
    return res;
}

int main(int argc, char const *argv[]) {
    int n;
    int res = 1;
    scanf("%d", &n);
    long int ns = 1 + powOfTwo(n - 1);
    long int nums[ns];
    if (n != 1) {
        for (int i = 0; i < ns / 2; i++) {
            nums[i] =
        }
    } else res = 1;

    printf("%d\n", res);

    return 0;
}
