#include <stdio.h>

float power(float x, int n) {
    float temp = 1;
    for (int i = 0; i < n; i++) {
        temp = temp * x;
    }
    return temp;
}

int factorial(int x) {
    int temp = 1;
    for (int i = 2; i <= x; i++) {
        temp *= i;
    }
    return temp;
}

float sine(float x) {
    while (x > 180) {
        x -= 360;
    }
    while (x < -180) {
        x += 360;
    }
    x /= 57.2958;
    float temp = 0;
    for (int i = 1; i < 10; i++) {
        temp += power(-1, i + 1) * power(x, 2 * i - 1) / factorial(2 * i - 1);
    }
    return temp;
}

void right(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void isosceles(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = n - i; j > 0; j--) {
            printf(" ");
        }
        for (int j = 0; j < 2 * i - 1; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void multTable() {
    for (int i = 1; i <= 10; i++) {
        for(int j = 1; j <= 10; j++){
            printf("%d * %d = %d\n", i, j, i * j);
        }
        printf("\n");
    }
}

float square(float x) {
    float prev = x;
    float initial = x;
    for (int i = 2; i < 10; i++) {
        prev = initial;
        initial = 1.0 / 2.0 * (prev + x / prev);
    }
    return initial;
}

int main() {
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    printf("%f\n", square(x));
    return 0;
}
