#include <stdio.h>
#include <stdlib.h>

int n_b(char* addr, int i) {
    return (((char)0x1) & ((char)*(addr + i/8)) >> i%8);
}

char d2c(int n) {
    return (n < 0 ? '?': (n < 10 ? '0'+n : (n < 36 ? 'A' + (n-10) : '?')));
}

long long int P2(int n) {
  return (n < 0 ? 0 : (n == 0 ? 1 : 2 * P2(n - 1)));
}

// Functions to complete

void base2(int n) {
    if (n <= 0) {
        return;
    }
    base2(n/2);
    printf("%d", n % 2);
}

void baseB(int B, int n) {
    if (B < 2 || B > 36) return;
    if (n <= 0) {
        return;
    }
    baseB(B, n / B);
    printf("%c", d2c(n  % B));
}

void mantissa(float f, int result[]) {
    for (int i = 0; i < 23; i++) {
        result[i] = n_b((char*)&f, 31 - i);
    }
}

float mantissa_normalized(float f) {
    while (f >= 2) {
        f /= 2;
    }
    return f;
}

void exponent(float f, int result[]) {
    for (int i = 23; i < 31; i++) {
        result[i] = n_b((char*)&f, 31 - i);
    }
}

int exponent_no_bias(float f) {
    int count = 0;
    while (f >= 2) {
        f /= 2;
        count++;
    }
    while (f < 1) {
        f *= 2;
        count--;
    }
    return count;
}

int sign(float f) {
    return n_b((char*)&f, 0);
}

int main() {
    // int n = 1;
    // base2(n);
    // printf("\n");
    // baseB(36, 99999);

    // int test;
    // printf("Give a number to convert to binary: ");
    // scanf("%d", &test);
    // for (int i = 0; i < 32; i++) {
    //     printf("%d", n_b((char*)&test, i));
    // }
    // printf("\n");

    // int result[32];
    // for (int i = 32; i < 32; i++) {
    //     result[i] = 0;
    // }

    // float f = 9.75;
    // mantissa(f, result);
    // exponent(f, result);
    // result[0] = sign(f);
    // for (int i = 0; i < 32; i++) {
    //     printf("%d", result[i]);
    // }

    printf("%f\n", mantissa_normalized(9.75));
    printf("%d\n", exponent_no_bias(9.75));

    printf("\n");

    return 0;
}
