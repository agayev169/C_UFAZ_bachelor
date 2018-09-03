// Exercise 6A.1
// a) Write a function that exchange the values of 2 variables by using Call-By-Value
// b) Write a function that exchange the values of 2 variables by using Call-By-Reference
#include <stdio.h>

void swapByValue(int x, int y) {
    int temp = x;
    x = y;
    y = temp;
    printf("Values in swapByValue fuction:\nx: %d, y: %d\n", x, y);
}

void swapByRef(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
    printf("Values in swapByRef fuction:\nx: %d, y: %d\n", *x, *y);
}

int main() {
    int x = 0, y = 1;
    printf("Before calling a function\nx: %d, y: %d\n", x, y);
    swapByValue(x, y);
    // swapByRef(&x, &y);
    printf("After calling a function\nx: %d, y: %d\n", x, y);

    return 0;
}