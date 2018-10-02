#include <string.h>
#include <math.h>
#include <string.h>
#include "LL.h"
#include "HT.h"

char *readFile();
unsigned maxChar(LLNode *pList);
unsigned nbrChar(LLNode *pList);
double entropy(LLNode *pList);
unsigned char *str_to_bits(char *str, int size);
unsigned char *bits_to_str(char *bits, int size);

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
    str = (char*) calloc(2000, sizeof(char));
    int size = 0;
    int size_all = 0;
    do { 
        char *tmp = (char*) calloc(8, sizeof(char));
        findLetter(huffmanTree, tmp, tc[i], 0, &size);
        size_all += size;
        strcat(str, tmp);
        i++;

    } while(tc[i]!='\n');

    unsigned char* bits = str_to_bits(str, size_all);
    printf("str: %s, size: %d\n", str, size_all);
    fwrite(bits, 1, ceil(size_all / 8), wr);
    fclose(wr);

    return 0;
}

unsigned char *str_to_bits(char *str, int size) {
    unsigned char* bits_char = (char*) calloc(ceil(size / 8), sizeof(char));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 8 && j < (size - i * 8); j++) {
            bits_char[i] = bits_char[i] << 1;
            bits_char[i] += (str[i * 8 + j] - '0');
            // printf("bit: %d, str[%d]: %c\n", bits_char[i], i + j, str[i + j]);
        }
    }
    return bits_char;
}

unsigned char *bits_to_str(char *bits_char, int size) {
    // TODO
    unsigned char* str = (char*) calloc(size * 8, sizeof(char));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < 8; j++) {
            str[i * 8 + j] = (bits_char[i] >>  7 - j);
        }
    }
    return str;
}


char *readFile() {
    FILE *file = fopen("test.txt", "r");
    if (file == NULL) return NULL;  //could not open
    char *code;
    size_t n = 0;
    int c;
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size + 1);
    while ((c = fgetc(file)) != EOF) {
        code[n++] = (char)c;
    }
    code[n] = '\0';
    fclose(file);
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
