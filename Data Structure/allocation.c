/*
* Increasing size of array by 5 elements using dynamical allocation
*/

// Pseudo-code

/*
define variable size = 5
dynamical allocate array of 5 elements

define counter = 0
while counter is less than or equal to size variable
    if counter equals to size
        if user needs add more new elements
            add 5 to size variable
            dynamically reallocate array of size elements
        else if user does not need add more elements
            skip while loop
        end if
    end if
    if arr is NULL(Means there is no free space in the memory)
        Let user know that there is no free space in the memory and exit the program
    end if
    get the next value from user
    add it into array
end while

define variable nbZeros = 0
define variable counter = size - 1
while (counter greater than or equal to 0)
    if (counter'th element of array equals to 0)
        define insideCounter = counter
        while (insideCounter less than or equal to size - nbZeros)
            assign insideCounter'th element of array to (insideCounter + 1)'th element of array
            assign (insideCounter + 1)'th element to 0
        end while
        increase nbZeros by 1
    end if
end while

while (nbZeros is greater than or equal to 5)
    decrease size by 5
    decrease nbZeros by 5
    dynamically reallocate array of size elements
end while
*/

// C code

#include <stdio.h>
#include <stdlib.h>

int *expand(int *arr, int *size) {
    *size += 5;
    arr = (int*) realloc(arr, *size * sizeof(int));
    return arr;
}

int *deleteEmpty(int *arr, int *size) {
    int nbZeros = 0;
    for (int i = *size - 1; i >= 0; i--) {
        if (arr[i] == 0) {
            for (int j = i; j < *size - nbZeros - 1; j++) {
                arr[j] = arr[j + 1];
                arr[j + 1] = 0;
            }
            nbZeros++;
        }
    }

    while (nbZeros >= 5) {
        *size -= 5;
        nbZeros -= 5;
        arr = (int*) realloc(arr, *size * sizeof(int));
    }

    return arr;
}

int main(int argc, char const *argv[]) {
    int size = 5;
    int *arr = (int*) malloc(5);
    for (int i = 0; i <= size; i++) {
        if (i == size) {
            printf("Do you need to add more values? (y/n)\n");
            char moreElements;
            scanf(" %c", &moreElements);
            if (moreElements == 'y') {
                arr = expand(arr, &size);
            }
            else break;
        }
        if (arr == NULL) {
            printf("No free space in the memory!\n");
            return 0;
        }
        int val;
        scanf("%d", &val);
        arr[i] = val;
    }

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Deleting empty values...\n");

    arr = deleteEmpty(arr, &size);

    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
