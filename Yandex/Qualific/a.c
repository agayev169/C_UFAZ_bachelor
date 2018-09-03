#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[]) {
    unsigned long int n, k;
    scanf("%ld%ld", &n, &k);
    unsigned long int division = (int)ceil((float)n / (float)k * 2.0);
    unsigned long int subtraction = n - k + 1;
    unsigned long int res = (division < subtraction) ? division : subtraction;
    if (res > 1) printf("%ld\n", res);
    else printf("2\n");

    return 0;
}
