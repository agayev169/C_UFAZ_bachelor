#include <string.h>
#include <math.h>
#include "LL.h"
#include "HT.h"

char *readFile();
unsigned maxChar(LLNode *pList);
unsigned nbrChar(LLNode *pList);
double entropy(LLNode *pList);

int main(){
    LLNode *pList=NULL;
    int n;
    char cAction, l;
    char *tc=readFile();

    int i=0;
    do { //printf("%c",tc[i]);
        if(!LL_Search_L(pList, tc[i]))
            LL_add(&pList, tc[i], 1);
        i++;
    } while(tc[i]!='\n'); //'\0' for multi lines
    // free(tc);
    LL_Print(pList);
    LLNode *psList = NULL;
    while(pList) {
        LLNode *temp=pList->pNext;
        LL_sorted_add(&psList, pList->ch, pList->nVal);
        free(pList);
        pList=temp;
    }
    LL_Print(psList);
    printf("The entropy value of the file is: %lf \n",entropy(psList));

    HLNode *hlist=readList(psList);
    HuffNode *huffmanTree=buildTree(hlist);
    printHTree(huffmanTree);
    // printf("\n");

    char *str = (char*) calloc(10, sizeof(char));
    printf("\n");
    printChar(huffmanTree, str, 0);
    printf("\n");
    // str = (char*) calloc(10, sizeof(char));
    // int size = 0;
    // findLetter(huffmanTree, str, ' ', 0, &size);
    // for (int i = 0; i < size; i++) {
    //     printf("%c", str[i]);
    // }
    // printf("%s", tmp);
    FILE *wr = fopen("test_bin.bin", "wb");
    i = 0;
    do { //printf("%c",tc[i]);
        str = (char*) calloc(10, sizeof(char));
        int size = 0;
        findLetter(huffmanTree, str, tc[i], 0, &size);
        for (int i = 0; i < size; i++) {
            fprintf(wr, "%c", str[i]);
        }
        i++;
    } while(tc[i]!='\n');

    return 0;
}


char *readFile() {
    FILE *file = fopen("test.txt", "r");
    char *code;
    size_t n = 0;
    int c;
    if (file == NULL) return NULL;  //could not open
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);
    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }
    code[n] = '\0';
    return code;
}

unsigned maxChar(LLNode *pList){
    unsigned nbChar = 0;
    while (pList) {
        nbChar += pList->nVal;
        pList = pList->pNext;
    }
    return nbChar;
}

unsigned nbrChar(LLNode *pList){
    unsigned nbChar = 0;
    while (pList) {
        nbChar++;
        pList = pList->pNext;
    }
    return nbChar;
}

double entropy(LLNode *pList){
    unsigned nbChars = maxChar(pList);
    double entrop = 0, prob, f;
    while (pList) {
        prob = pList->nVal / (float) nbChars;
        f = prob * log2(1 / prob);
        entrop += f;
        pList = pList->pNext;
    }
    return entrop;
}
