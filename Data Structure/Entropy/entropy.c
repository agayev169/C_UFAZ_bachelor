#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float calculate_entropy(char *filename);
float entropy(long symbols[], long count);

int main(int argc, char *argv[]) {
    // char *filename = "Deitel-C_ How to Program.pdf";
    // printf("Filename: ");
    // scanf("%s", filename);
    char *filename = argv[1];
    float entropy = calculate_entropy(filename);
    
    printf("Entropy: %f\n", entropy);

    return 0;
}

float calculate_entropy(char *filename) {
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Cannot open file!\n");
        exit(1);
    }

    long symbols[256];
    for (int i = 0; i < 256; i++) {
        symbols[i] = 0;
    }

    long count = 0;
    while(!feof(file)) {
        char c;
        fread(&c, 1, 1, file);
        symbols[c]++;
        count++;
    }
    fclose(file);

    return entropy(symbols, count);
}

float entropy(long symbols[], long count) {
    float result = 0;
    for (int i = 0; i < 256; i++) {
        if (symbols[i] == 0) continue;
        result -= ((float) symbols[i] / (float) count) * log2(((float) symbols[i] /(float) count));
    }
    return result;
} 