#include <stdio.h>
#include <math.h>

// int stopedIncreasing(char c[], int size) {
//     for (int i = 0; i < size - 1; i++) {
//         if (c[i+1] <= c[i]) {
//             return i + 2;
//         }
//     }
//     return size;
// }
//
// int stopedDecreasing(char c[], int size) {
//     for (int i = 0; i < size - 1; i++) {
//         if (c[i+1] >= c[i]) {
//             return i + 2;
//         }
//     }
//     return size;
// }

int findMin(int digits[]) {
    int index;
    for (int i = 0; i < 10; i++) {
        if (digits[i] != 0) {
            index = i;
            break;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (digits[i] < digits[index] && digits[i] != 0) index = i;
    }
    return index;
}

int main(int argc, char const *argv[]) {
    char first[100];
    scanf("%s", first);

    int count = 0;
    while (first[count] != '\0') {
        count++;
    }
    int size = count;
    char c[size];

    count = 0;
    while (first[count] != '\0') {
        c[count] = first[count];
        count++;
    }

    int digits[10];

    for (int i = 0; i < 10; i++) {
        digits[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        digits[(int)c[i] - 48]++;
    }

    long unsigned int index = findMin(digits);

    index = pow(2, digits[index] - 1);
    printf("%ld\n", index);

    // int incr = stopedIncreasing(c, size);
    // int decr = stopedDecreasing(c, size);

    // long unsigned int index = (incr < decr) ? decr : incr;
    // index = pow(2, size - index);

    // printf("%ld\n", index);

    return 0;
}
