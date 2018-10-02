#include <string.h>
#include <math.h>
#include <string.h>
#include "LL.h"
#include "HT.h"

char *readFile(char *filename);
unsigned maxChar(LLNode *pList);
unsigned nbrChar(LLNode *pList);
double entropy(LLNode *pList);
unsigned char *str_to_bits(char *str, int size);
unsigned char *bits_to_str(unsigned char *bits, int size, int str_size);


int main() {
    LLNode *pList=NULL;
    int n;
    char cAction, l;
    char *tc=readFile("test.txt");

    int i=0;
    do {
        if(!LL_Search_L(pList, tc[i]))
            LL_add(&pList, tc[i], 1);
        i++;
    } while(tc[i]!='\n');
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

    char *str = (char*) calloc(8, sizeof(char));
    printf("\n");
    printChar(huffmanTree, str, 0);
    printf("\n");
    i = 0;
    str = (char*) calloc(100, sizeof(char));
    int size = 0;
    int size_all = 0;
    do { 
        char *tmp = (char*) calloc(8, sizeof(char));
        findLetter(huffmanTree, tmp, tc[i], 0, &size);
        // str = (char*) realloc(str, (size_all + size) * sizeof(char));
        for (int j = size_all; j < size_all + size; j++) {
            str[j] = tmp[j - size_all];
        }
        size_all += size;
        i++;
    } while(tc[i]!='\n');
    free(tc);

    unsigned char* bits = str_to_bits(str, size_all);
    printf("str: %s, size: %d\n", str, size_all);
    FILE *wr = fopen("test_bin.bin", "wb");
    int size_of_header = 0;
    fwrite(&size_of_header, 4, 1, wr);
    str = (char*) calloc(8, sizeof(char));
    printCharToFile(wr, huffmanTree, str, 0);
    size_of_header = ftell(wr);
    fseek(wr, 0, SEEK_SET);
    fwrite(&size_of_header, 4, 1, wr);
    fseek(wr, size_of_header, SEEK_SET);
    fwrite(&size_all, 4, 1, wr);
    fwrite(bits, 1, ceil(size_all / 8.0), wr);
    fclose(wr);

    free(bits);
    free(str);
    return 0;
}

unsigned char *str_to_bits(char *str, int size) {
    unsigned char* bits_char = (char*) calloc(ceil(size / 8.0), sizeof(char));
    for (int i = 0; i < ceil(size / 8.0); i++) {
        for (int j = 0; j < 8 && j < (size - i * 8); j++) {
            bits_char[i] = bits_char[i] << 1;
            bits_char[i] += (str[i * 8 + j] - '0');
        }
    }
    return bits_char;
}

unsigned char *bits_to_str(unsigned char *bits_char, int size, int str_size) {
    unsigned char* str = (char*) calloc(str_size, sizeof(char));
    for (int i = 0; i < size; i++) {
        int j = 7;
        while (i * 8 + j >= str_size) {
            j--;
        }
        for (; j >= 0; j--) {
            str[i * 8 + j] = (bits_char[i] % 2) + '0';
            bits_char[i] /= 2;
        }
    }
    return str;
}


char *readFile(char *filename) {
    FILE *file = fopen(filename, "r");
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
