#include <stdio.h>
#include <stdlib.h>

int max_subarray(int *dif, int size);
// int max_subarray(char *matches, int size);
int matches(char *genome, char *mutation);
int difference(char *matches, int size);
int global_max(int *array, int size);
int *max_sum(char *matches, int size);

int matches(char *genome, char *mutation) {
    size_t genome_n = strlen(genome);
    size_t mutation_n = strlen(mutation);
    int max_score = 0;
    int index = 0;
    char *gr = (char*) calloc(mutation_n, sizeof(char));

    for (int i = 0; i <= genome_n - mutation_n; i++) {
        for (int j = 0; j < mutation_n; j++) {
            gr[j] = (genome[i + j] == mutation[j]) ? 1 : -1;
        }
        // int *dif = difference(gr, mutation_n);
        // int score = max_subarray(dif, mutation_n + 1);
        int score = difference(gr, mutation_n);
        if (max_score < score) {
            max_score = score;
            index = i;
        }
        // free(dif);
    }
    free(gr);
    printf("max_score: %d\n", max_score);
    return index;
}

int max_subarray(int *dif, int size) {
    int max_score = 0; 
    for (int i = 0; i < size - 1; i++) {
        if (dif[i] > dif[i + 1]) continue;
        int max_index = global_max(dif + i, size - i);
        int score = dif[i + max_index] - dif[i];
        if (score > max_score) {
            max_score = score;
        }
    }
    return max_score;
}

// int max_subarray(char *matches, int size) {
//     int score = 0;
//     int len = 0;
//     int index = 0;
//     int res = (int*) calloc(2, sizeof(int));
//     for (int i = 0; i < size; i++) {
//         if (matches[i] == 1) {
//             int *cur = max_sum(matches + i, size - i);
//             // printf("%d: %d, %d\n", i, cur[0], cur[1]);
//             if (cur[0] > score) {
//                 score = cur[0];
//                 len = cur[1];
//                 index = i;
//             }
//             free(cur);
//         }
//     }
//     res = score;
//     return res;
// }

int global_max(int *dif, int size) {
    int max_val = dif[0];
    int index = 0;
    for (int i = 1; i < size; i++) {
        if (dif[i] > max_val) {
            max_val = dif[i];
            index = i;
        }
    }
    return index;
}

int *max_sum(char *matches, int size) {
    int max_sum = 0;
    int max_len = 0;
    int sum = 0;
    int len = 0;
    for (int i = 0; i < size; i++) {
        sum += matches[i];
        len++;
        if (sum >= max_sum) {
            max_sum = sum;
            max_len = len;
        }
    }
    int *res = (int*) calloc(2, sizeof(int));
    res[0] = max_sum;
    res[1] = max_len;
    return res;
}

int difference(char *matches, int size) {
    int cum_score = 0;
    int best_score = 0;
    int global_min = 0;
    for (int i = 0; i < size; i++) {
        if (matches[i] == 1) cum_score++;
        else cum_score--;
        if (cum_score < 0) {
            global_min = i;
            cum_score = 0;
        } else if (cum_score >= best_score) {
            best_score = cum_score;
        }
    }

    // printf("best_score: %d, global_min: %d", best_score, global_min);
    return best_score;
}