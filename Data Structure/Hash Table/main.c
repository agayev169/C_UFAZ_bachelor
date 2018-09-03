#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define SIZE 11


int main(int argc, char const *argv[]) {
    LinkedListString *list[SIZE];
    int n = 0;
    char act;

    char *text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";


    for (int i = 0; i < SIZE; i++)
        list[i] = NULL;

    do {
        printf("(l)oad, (p)rint, (d)elete a word, (D)estruct, (h)ash, (q)uit: ");
        scanf(" %c", &act);
        if (act == 'l') {
            char *pCur = text, word[50];
            while (*pCur) {
                sscanf(pCur, " %s", word);
                for (int i = 0; word[i]; i++) pCur++;
                if (*pCur) pCur++;
                add(list + hash(word, SIZE), word);
            }
        } else if (act == 'h') {
            char word[50];
            printf("Enter a word to hash its value: ");
            scanf("%s", word);
            printf("Hash value of %s: %d\n", word, hash(word, SIZE));
        } else if (act == 'p') {
            for (int i = 0; i < SIZE; i++) {
                printf("\n");
                print(list[i]);
            }
        } else if (act == 'D') {
            for (int i = 0; i < SIZE; i++) {
                destroy(list + i);
            }
            printf("Destructed\n");
        } else if (act == 'd') {
            char word[50];
            printf("Enter a word to delete it: ");
            scanf("%s", word);
            del(list + hash(word, SIZE), word);
        } else if (act != 'q'){
            printf("Unknown symbol\n");
        }
    } while (act != 'q');

    return 0;
}

