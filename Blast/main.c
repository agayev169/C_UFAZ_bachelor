#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "genome.c"


char mutate(char *word, int mutation_rate);
char *read_genome(char *path);
char *read_genome_with_mutation(char *path, char *mutation);
char *random_string(int size, char *letters);

int main(int argc, char *argv[]) {
    srand(time(NULL));
    char *genome = read_genome("data.csv");
    char *mutation = (char*) calloc(100, sizeof(char));
    int index_mut = rand() % (strlen(genome) - 100);
    for (int i = index_mut; i < index_mut + 100; i++) {
        mutation[i - index_mut] = genome[i];
    }

    // printf("genome  : %s\n", genome);
    // printf("mutation: %s\n", mutation);
    mutate(mutation, 10);
    printf("mutation: %s\n", mutation);

    int index = matches(genome, mutation);
    printf("index: %d\n", index);

    free(genome);
    free(mutation);

    // char matches[] = {-1, 1, -1, 1, 1, 1, 1};
    // difference(matches, 7);

    return 0;
}

char mutate(char *word, int mutation_rate) {
    // 0 <= mutation_rate <= 100
    size_t word_n = strlen(word);
    for (int i = 0; i < word_n; i++) {
        if (rand() % 101 < mutation_rate) {
            char c = word[i];
            while (c == word[i]) {
                word[i] = "acgt"[rand() % 4];
            }
            // printf("%d: %c mutated to %c\n", i, c, word[i]);
        }
    }
}

char *read_genome_with_mutation(char *path, char *mutation) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Cannot open the file!\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    int end = ftell(f);
    fseek(f, 0, SEEK_SET);

    while (!feof(f)) {
        char *line = (char*) calloc(500, sizeof(char));
        fscanf(f, "%s", line);
        if (strcmp(line, "ORIGIN") == 0) {
            // printf("%s\n", line);
            free(line);
            break;
        }
        free(line);
    }

    const int MAX_SIZE = 300000;
    char *genome = (char*) calloc(MAX_SIZE, sizeof(char));
    int i = 0;

    int cur = ftell(f);
    int index_mutation = rand() % ((end - cur) / 2);
    char read_mutation = 0;
    int read_chars = 0;
    while (!feof(f) && i < MAX_SIZE) {
        char *line = (char*) calloc(100, sizeof(char));
        fscanf(f, "%s", line);
        int line_len = strlen(line);
        read_chars += line_len;
        for (int j = 0; j < line_len; j++) {
            if (line[j] != 'a' && line[j] != 'c' && line[j] != 'g' && 
            line[j] != 't') continue;
            genome[i++] = line[j];
            if (i >= MAX_SIZE) {
                break;
            }
        }

        if (!read_mutation && read_chars > index_mutation) {
            if (line[0] == 'a' || line[0] == 'c' || line[0] == 'g' || 
            line[0] == 't') {
                strcpy(mutation, line);
                read_mutation = 1;
            }
        }

        free(line);
    }

    genome = realloc(genome, (i + 1) * sizeof(char));
    printf("size of genome: %d\n", i);

    printf("size of mutation: %zu\n", strlen(mutation));

    fclose(f);
    return genome;
}

char *read_genome(char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Cannot open the file!\n");
        exit(1);
    }
    while (!feof(f)) {
        char *line = (char*) calloc(500, sizeof(char));
        fscanf(f, "%s", line);
        // printf("%s", line);
        if (strcmp(line, "ORIGIN") == 0) {
            // printf("%s\n", line);
            break;
        }
        free(line);
    }
    const int MAX_SIZE = 300000;
    char *genome = (char*) calloc(MAX_SIZE, sizeof(char));
    int i = 0;
    while (!feof(f) && i < MAX_SIZE) {
        char *line = (char*) calloc(100, sizeof(char));
        fscanf(f, "%s", line);
        int line_len = strlen(line);
        for (int j = 0; j < line_len; j++) {
            if (line[j] != 'a' && line[j] != 'c' && line[j] != 'g' && 
            line[j] != 't') continue;
            genome[i++] = line[j];
            if (i >= MAX_SIZE) {
                break;
            }
        }
        free(line);
    }
    genome = realloc(genome, i * sizeof(char));
    printf("size of genome: %d\n", i);

    fclose(f);
    return genome;
}

char *random_string(int size, char *letters) {
    int letters_size = strlen(letters);
    char *str = (char*) calloc(size, sizeof(char));
    for (int i = 0; i < size; i++) {
        int index = rand() % letters_size;
        str[i] = letters[index];
    }
    return str;
}