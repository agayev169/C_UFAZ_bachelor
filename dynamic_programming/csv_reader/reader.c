#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

float *readCSV(char *path, int col, int objects_n);

int main(int argc, char *argv[]) {
    float *data = readCSV("data.csv", 6, 5);
    for (int i = 0; i < 5; i++) {
        printf("%f\n", data[i]);
    }

    return 0;
}


float *readCSV(char *path, int col, int objects_n) {
    float *data = (float*) calloc(objects_n, sizeof(float));
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Cannot find a file!\n");
        exit(1);
    }

    int i = 0;
    while (!feof(f) && i < objects_n) {
        char *tmp = (char*) calloc(20, sizeof(char*));
        int j = 0;
        int count = 0;
        while (1) {
            fscanf(f, "%c", &(tmp[j]));
            printf("tmp[%d]: %c\n", j, tmp[j]);
            if (count >= 5 && ((tmp[j] > '9' || tmp[j] < '0') && tmp[j] != '.')) break;
            if ((tmp[j] > '9' || tmp[j] < '0') && tmp[j] != '.') {
                count++;
                j = -1;
            }
            j++;
        }
        tmp = realloc(tmp, (j + 1) * sizeof(char));
        printf("str: %s\n", tmp);
        data[i++] = atof(tmp);
        free(tmp);
    }

    // int i = 0;
    // char str[1000], *pIn;
    // do{
    //     fscanf(f, "%s", str);
    //     // printf("str: %s\n", str);
    //     pIn = strtok(str, ";");//PointerToString=strtok(PointerToTheString,constCharAS delimiter)
    //     int count = 0;
    //     while(pIn != NULL) {
    //         printf("pIn: %s\n", pIn);
    //         if (count >= 6) {
    //             // printf("%f  ", atof(pIn));
    //             data[i++] = atof(pIn);
    //             break;
    //         }
    //         pIn = strtok(NULL, ";"); //to a new data
    //         count++;
    //     }
    // } while (fgetc(f) != EOF && i <= objects_n);

    // fclose(f);
    return data;
}