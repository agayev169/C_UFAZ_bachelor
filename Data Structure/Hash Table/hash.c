#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

//-------Table--------

int add(LinkedListString **list, char *s) {
    LinkedListString *newN = *list;
    if (*list == NULL) {
        *list = (LinkedListString*)malloc(sizeof(LinkedListString));
        strcpy((*list)->w.s, s);
        (*list)->w.n = 1;
        (*list)->next = NULL;
        return 0;
    }
    for(; (newN->next) && (strcmp(newN->w.s, s)); newN = newN->next);
    if (!strcmp(s, newN->w.s)) newN->w.n++;
    else {
        if (!(newN->next = (LinkedListString*)malloc(sizeof(LinkedListString)))) {
            fprintf(stderr, "Error! No memory to create a new node\n");
            exit(1);
        }
        strcpy(newN->next->w.s, s);
        newN->next->w.n = 1;
        newN->next->next = NULL;
    }
    return 0;
}

int del(LinkedListString **list, char *s) {
    if (*list == NULL) return 1;
    if (strcmp((*list)->w.s, s) == 0) {
        if ((*list)->w.n == 1) {
            *list = (*list)->next;
            return 0;
        } else {
            (*list)->w.n--;
        }
    }
    
    for (LinkedListString *i = *list; i->next != NULL; i = i->next) {
        // printf("Next value: %d\n", i->next->s);
        if (strcmp(i->next->w.s, s) == 0) {

            if (i->next->w.n == 1) {
                i->next = i->next->next;
                return 0;
            } else {
                i->next->w.n--;
            }

            // LinkedListString *temp = i;
            // i->next = i->next->next;;
            return 0;
        }
    }
    return 1;
}

int print(LinkedListString *list) {
    printf("\n");
    printf("[XXXX]-->");
    if (list == NULL) {
        printf("/\n");
        return 1;
    }
    LinkedListString *pCur;
    for (pCur = list; pCur; pCur = pCur->next) {
        printf("(%s, %d)-->", pCur->w.s, pCur->w.n);
    }
    printf("/\n");
    printf("/\n");
    return 0;
}

int destroy(LinkedListString **list) {
    if (*list != NULL) {
        destroy(&((*list)->next));
        free(*list);
        *list = NULL;
    }
    return 0;
}

//-------Hash---------

int hash(char *word, int n) {
    int h = 0;
    int i;
    for (i = 0; word[i]; i++)
        h = (h * 256 + word[i]) % n;
    // printf("Word: %s\tHash: %d\n", word, h);
    return h;
}
