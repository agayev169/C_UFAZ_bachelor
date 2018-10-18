#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "genome.c"

char *read_genome(char *path);
char *random_string(int size, char *letters, int letters_size);
const int MUTATION_N = 100;

int main(int argc, char *argv[]) {
    srand(time(NULL));
    // char *genome = random_string(GENOME_N, "ACGT", 4);
    char *genome = read_genome("data.csv");
    const int GENOME_N = strlen(genome);
    char *mutation = random_string(MUTATION_N, "acgt", 4);

    // printf("genome  : %s\n", genome);
    // printf("mutation: %s\n", mutation);

    int index = matches(genome, GENOME_N, mutation, MUTATION_N);
    printf("index: %d\n ", index);

    free(genome);
    free(mutation);

    return 0;
}

char *read_genome(char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Cannot open the file!\n");
        exit(1);
    }

    while (!feof(f)) {
        char *line = (char*) calloc(100, sizeof(char));
        fscanf(f, "%s", line);
        if (strcmp(line, "ORIGIN") == 0) {
            printf("%s\n", line);
            break;
            
        }
        free(line);
    }
    printf("OK\n");
    const int MAX_SIZE = 300000;
    char *genome = (char*) calloc(MAX_SIZE, sizeof(char));
    int i = 0;
    while (!feof(f) && i < MAX_SIZE) {
        char *line = (char*) calloc(100, sizeof(char));
        // fscanf(f, "%[^\n]s", line);
        fgets(line, 100, f);
        int line_len = strlen(line);
        // printf("%s\n", line);
        for (int j = 0; j < line_len; j++) {
            if (line[j] != 'a' && line[j] && 'c' && line[j] != 'g' && 
            line[j] != 't') continue;
            genome[i++] = line[j];
            if (i >= MAX_SIZE) {
                break;
            }
            // if (i % 100 == 0 && i != 0) printf("%d ", i);
        }
        // printf("%d  ", i);
        free(line);
    }
    genome = realloc(genome, i * sizeof(char));
    printf("size of genome: %d\n", i);

    fclose(f);
    return genome;
}

char *random_string(int size, char *letters, int letters_size) {
    char *str = (char*) calloc(size, sizeof(char));
    for (int i = 0; i < size; i++) {
        int index = rand() % letters_size;
        str[i] = letters[index];
    }
    return str;
}