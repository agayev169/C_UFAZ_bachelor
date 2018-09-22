#include <stdio.h>
#include <stdlib.h>

void compress(char *str);
void compress2(char *str);
void decompress(char *str);
int next_int(char *str, int *pos);
void decompress2(char *str);

int main(int argc, char *argv[]) {
    char str[140];
    printf("String: ");
    scanf("%s", str);
    decompress2(str);

    return 0;
}

// Compression

void compress(char *str) {
    // Compresses indicating only the number of same chars even if the number == 1
    // Not Recomended
    char c = str[0];
    char prev = c;
    int count = 1;

    for (int i = 1; prev != '\0'; i++) {
        prev = c;
        c = str[i];
        if (c == prev) {
            count++;
        } else {
            printf("%d%c", count, prev);
            count = 1;
        }
    }
    printf("\n");
}

void compress2(char *str) {
    // Compresses indicating both the number of same chars and different chars
    // Recomended

    char c = str[0];
    char prev = c;
    int count_same = 1;
    int count_dif = 0;

    for (int i = 1; prev != '\0'; i++) {
        prev = c;
        c = str[i];
        if (c == prev && count_dif == 0) {
            count_same++;
        } else if (c != prev && count_same > 1) {
            printf("%d%c", count_same, prev);
            count_same = 1;
        } else if (c != prev && count_same == 1) {
            count_dif++;
        } else if (c == prev && count_dif > 0) {
            char *tmp = (char*) calloc(count_dif, sizeof(char));
            for (int j = 0; j < count_dif; j++) {
                tmp[j] = str[i - count_dif - 1 + j];
            }
            printf("%d%s", count_dif, tmp);
            count_dif = 0;
            i--;
        }
    }
    printf("\n");
}

// Decompression

void decompress(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        int count = next_int(str, &i);
        char c = str[i];
        for (int j = 0; j < count; j++) {
            printf("%c", c);
        }
    }
    printf("\n");
}

int next_int(char *str, int *pos) {
    int res = 0;
    int sign = 1; 
    if (str[*pos] == '-') {
        sign = -1;
        *pos += 1;    
    }
    while (str[*pos] != '\0' && str[*pos] <= 56 && str[*pos] >= 48) {
        char c = str[*pos];
        res = res * 10 + sign * (c - 48);
        *pos += 1;
    }
    return res;
}

void decompress2(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        int count = next_int(str, &i);
        // printf("count: %d\n", count);
        if (count > 0) {
            char c = str[i];
            for (int j = 0; j < count; j++) {
                printf("%c", c);
            } 
        } else if (count < 0) {
            for (int j = i; j < i - count; j++) {
                printf("%c", str[j]);
            }
            i = i - count - 1;
        }
    }
    printf("\n");
}