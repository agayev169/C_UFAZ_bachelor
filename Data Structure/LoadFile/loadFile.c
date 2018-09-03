#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NB_ELEMENT_MAX 100

int loadFile(char table[NB_ELEMENT_MAX]) {
    FILE *fp;
    int i = 0;
    fp = fopen("test.csv", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error in openning a file\n");
        exit(1);
    } else {
        while (i < NB_ELEMENT_MAX && fscanf(fp, "%c", &table[i]) == 1) {
            printf("table[%d] = %c\n", i, table[i]);
            i++;
        }
        fclose(fp);
    }
    return i;
}

int CSVReader(int A[NB_ELEMENT_MAX]) {
    int i = 0;
    FILE *pif;

    pif = fopen("test.csv", "r");
    if (pif == NULL) {
        fprintf(stderr, "Error in openning a file\n");
        exit(1);
    } else {
        char str[100], *pIn;
        fscanf(pif, "%s", str);
        pIn = strtok(str, ",");
        while (pIn != NULL) {
            A[i++] = atoi(pIn);
            pIn = strtok(NULL, ",");
        }
    }
    return i;
}

int show(char table[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%c", table[i]);
    }
    return i;
}

int showCSV(int A[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    return i;
}

int main(int argc, char const *argv[]) {
    int A[NB_ELEMENT_MAX];
    showCSV(A, CSVReader(A));
    printf("\n");
    return 0;
}
