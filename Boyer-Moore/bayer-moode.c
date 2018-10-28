#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarations
int find_in_word(char *to_find, char *word);
int find_in_arr(char *arr, char c, int start);

// Definitions
int find_in_word(char *to_find, char *word) {
    size_t to_find_len = strlen(to_find);
    size_t word_len = strlen(word);
    char *shift = (char*) calloc(to_find_len, sizeof(char));
    for (size_t i = 0; i < to_find_len; i++) {
        shift[i] = to_find[to_find_len - i - 1];
    }

    for (size_t i = 0; i < word_len;) {
        size_t count = 0;
        while (count < to_find_len && 
            word[to_find_len + i - count - 1] == to_find[to_find_len - count - 1]) {
            // printf("to_find[%zu]: %c, word[%zu]: %c\n", to_find_len - count - 1, 
            //     to_find[to_find_len - count - 1], to_find_len + i - count - 1, 
            //     word[to_find_len + i - count - 1]);
            count++;
        }
        if (count >= to_find_len) return i;
        i += find_in_arr(shift, word[to_find_len + i - count - 1], count + 1);
    }

    free(shift);
    return -1;
}

int find_in_arr(char *arr, char c, int start) {
    size_t arr_len = strlen(arr);
    for (size_t i = start; i < arr_len; i++) {
        if (c == arr[i]) {   
            return i;
        }
    }
    return arr_len;
}