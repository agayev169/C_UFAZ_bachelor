#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_subarray(int *dif, int size);
// int max_subarray(char *matches, int size);
int matches(char *genome, char *mutation);
int difference(char *matches, int size);
int global_max(int *array, int size);
int *max_sum(char *matches, int size);
int max_of_four(int x1, int x2, int x3);

int matches(char *genome, char *mutation) {
    size_t genome_len = strlen(genome);
    size_t mutation_len = strlen(mutation);
    int max_score = 0;

    int max_x = 0;
    int max_y = 0;

    int **dif = (int**) calloc(mutation_len + 1, sizeof(int*));
    for (int i = 0; i < mutation_len + 1; i++) {
        dif[i] = (int*) calloc(genome_len + 1, sizeof(int));
        if (i != 0) {
            for (int j = 1; j < genome_len + 1; j++) {
                int match = (mutation[i - 1] == genome[j - 1]) ? 3 : 
                ((mutation[i - 1] == 'a' && genome[j - 1] == 'g') || 
                (mutation[i - 1] == 'g' && genome[j - 1] == 'a') ||
                (mutation[i - 1] == 'c' && genome[j - 1] == 't') || 
                (mutation[i - 1] == 't' && genome[j - 1] == 'c')) ? -1 : -3;
                dif[i][j] = max_of_four(dif[i - 1][j - 1] + match, 
                dif[i - 1][j] - 2, dif[i][j - 1] - 2);
                if (dif[i][j] >= max_score) {
                    max_x = j;
                    max_y = i;
                    max_score = dif[i][j];
                }
            }
        }
    }
    // printf("   ");
    // for (int i = 0; i < genome_len; i++) {
    //     printf(" %c", genome[i]);
    // }
    // for (int i = 0; i < mutation_len + 1; i++) {
    //     if (i != 0) printf("\n%c", mutation[i - 1]);
    //     else printf("\n ");
    //     for (int j = 0; j < genome_len + 1; j++) {
    //         printf(" %d", dif[i][j]);
    //     }
    // }
    // printf("\n");

    
    char *tmp = (char*) calloc(200, sizeof(char));
    int count = 0;
    while (max_x > 0 && max_y > 0 && dif[max_y][max_x] > 0) {
        // printf("max_x: %d, max_y: %d, count: %d\n", max_x, max_y, count);
        if (dif[max_y - 1][max_x] - dif[max_y][max_x] == 2) max_y--;
        else if (dif[max_y][max_x - 1] - dif[max_y][max_x] == 2) {tmp[count++] = '_'; max_x--;}
        else {tmp[count++] = mutation[--max_y]; max_x--;}
    }

    size_t tmp_len = strlen(tmp);
    tmp = realloc(tmp, tmp_len * sizeof(char));
    for (size_t i = 0; i < tmp_len / 2; i++) {
        char temp = tmp[i];
        tmp[i] = tmp[tmp_len - i - 1];
        tmp[tmp_len - i - 1] = temp;
    }

    printf("original: %s\n", tmp);
    for (int i = 0; i < mutation_len + 1; i++) {
        free(dif[i]);
    }
    free(dif);
    free(tmp);

    return max_x;
}

int max_of_four(int x1, int x2, int x3) {
    if (x1 >= x2 && x1 >= x3 && x1 >= 0) {
        return x1;
    } 
    if (x2 >= x1 && x2 >= x3 && x2 >= 0) {
        return x2;
    } 
    if (x3 >= x1 && x3 >= x2 && x3 >= 0) {
        return x3;
    } 
    return 0;
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