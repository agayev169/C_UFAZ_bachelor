#ifndef _LZW_H_
#define _LZW_H_

#include <stdio.h>

typedef struct LZWList {
    char* ch;
    int chSize;
    int code;
    struct LZWList *next;
} LZWList;

void add(LZWList **pList, char *ch, int size);
int find(LZWList *pList, char *ch, int size);
void compress(char *rFileName, char *wrFileName, LZWList **pList);
void printList(LZWList *pList);

#endif