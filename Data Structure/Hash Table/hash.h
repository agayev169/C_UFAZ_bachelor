#ifndef _HASH_H_
#define _HASH_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Word {
    char s[50];
    int n;
} Word;

// ---------Table----------

typedef struct LinkedListString {
    Word w;
    struct LinkedListString *next;
} LinkedListString;

int add(LinkedListString **list, char *s);
int del(LinkedListString **list, char *s);
int print(LinkedListString *list);
int destroy(LinkedListString **list);

// ---------Hash-----------

int hash(char *word, int n);

#endif
