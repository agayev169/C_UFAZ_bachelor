#include "lzw.h"
#include <stdio.h>
#include <stdlib.h>


void add(LZWList **pList, char *ch, int size) {
    if (!*pList) {
        *pList = (LZWList*) calloc(1, sizeof(LZWList));
        (*pList)->ch = (char*) calloc(size, sizeof(char));
        (*pList)->ch = ch;
        // (*pList)->ch = (char*) realloc(ch, sizeof(char));
        (*pList)->chSize = size;
        (*pList)->code = 256;
        (*pList)->next = NULL;
    } else {
        LZWList *tmp = (LZWList*) calloc(1, sizeof(LZWList));
        tmp->ch = (char*) calloc(size, sizeof(char));
        tmp->ch = ch;
        tmp->chSize = size;
        tmp->code = (*pList)->code + 1;
        tmp->next = *pList;
        *pList = tmp;
    }
}

int find(LZWList *pList, char *ch, int size) {
    if (size == 2) {
        return (int) ch[0];
    }
    while (pList != NULL) {
        if (pList->ch == ch) {
            return pList->code;
        }
        pList = pList->next;
    }
    return -1;
}

void compress(char *rFileName, char *wrFileName, LZWList **pList) {
    FILE *r = fopen(rFileName, "r");
    FILE *wr = fopen(wrFileName, "w");
    char c;

    char *str;
    int strSize = 2;
    str = (char*) calloc(2, sizeof(char));

    char *prev;
    int prevSize = 2;
    prev = (char*) calloc(2, sizeof(char));
    str[0] = getc(r);
    while ((c = getc(r)) != EOF) {
        if (strSize > 2 && find(*pList, str, strSize) == -1) {
            printf("Adding new value into library:\n");
            printf("str[prevSize] = %c\t\tstr[prevSize - 1] = %c\n", str[prevSize], str[prevSize - 1]);
            printf("str: %s, prev: %s, c: %c\n", str, prev, c);
            printf("prevSize: %d, strSize: %d\n\n", prevSize, strSize);
            add(pList, str, strSize);
            fprintf(wr, "%d ", find(*pList, prev, prevSize));
            strSize = 2;
            prevSize = 2;
            str = (char*) calloc(2, sizeof(char));
            prev = (char*) calloc(2, sizeof(char));
            str[0] = c;
            // fseek(r, -1, SEEK_CUR);
            continue;
        }

        // printf("str: %s, prev: %s\n", str, prev);
        // printf("prevSize: %d, strSize: %d\n\n", prevSize, strSize);
        // prevSize = strSize;
        // prev = (char*) calloc(prevSize, sizeof(char));
        // for (int i = 0; i < prevSize; i++) {
        //     prev[i] = str[i];
        // }
        // printf("str: %s, prev: %s\n", str, prev);
        // printf("prevSize: %d, strSize: %d\n\n", prevSize, strSize);

        // strSize++;
        // str = (char*) calloc(strSize, sizeof(char));
        // for (int i = 0; i < prevSize; i++) {
        //     str[i] = prev[i];
        // }
        // str[prevSize] = c;
        // printf("str: %s, prev: %s, c: %c\n", str, prev, c);
        // printf("prevSize: %d, strSize: %d\n\n", prevSize, strSize);
        // printf("str: %s, prev: %s, c: %c\n", str, prev, c);
        // printf("prevSize: %d, strSize: %d\n\n", prevSize, strSize);
        char *temp = prev;
        prev = str;
        free(temp);
        prevSize = strSize;
        printf("str: %s, prev: %s, c: %c\n", str, prev, c);
        printf("prevSize: %d, strSize: %d\n\n", prevSize, strSize);
        strSize++;
        char *str = calloc(strSize, sizeof(char));
        
        for (int i = 0; i < prevSize; i++) {
            // printf("prev[%d]: %s\n", i, prev);
            str[i] = prev[i];
        }
        str[prevSize] = str[prevSize - 1];
        str[prevSize - 1] = c;
        printf("str[prevSize] = %c\t\tstr[prevSize - 1] = %c\n", str[prevSize], str[prevSize - 1]);

        printf("str: %s, prev: %s, c: %c\n", str, prev, c);
        printf("prevSize: %d, strSize: %d\n\n", prevSize, strSize);
    }
}

void printList(LZWList *pList) {
    while (pList) {
        printf("(%s, %d) -> ", pList->ch, pList->code);
        pList = pList->next;
    }
    printf("//\n");
}