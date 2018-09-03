#include <stdio.h>

void isTriangle(unsigned long long int lengths[], int n, int x) {
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if ((lengths[i] + lengths[j] > lengths[k]) &&
                    (lengths[i] + lengths[k] > lengths[j]) &&
                    (lengths[k] + lengths[j] > lengths[i])) {
                    printf("%d %d %d\n", i + 1 + x, j + 1 + x, k + 1 + x);
                    return;
                }
            }
        }
    }
    printf("-1\n");
}

int main(int argc, char const *argv[]) {
    int n, q;
    scanf("%d%d", &n, &q);
    unsigned long long int lengths[n];
    for (int i = 0; i < n; i++) {
        scanf("%llu", &lengths[i]);
    }
    int intervals[q][2];
    for (int i = 0; i < q; i++) {
        scanf("%d%d", &intervals[i][0], &intervals[i][1]);
    }
    for (int i = 0; i < q; i++) {
        isTriangle(lengths + intervals[i][0] - 1, intervals[i][1] - intervals[i][0] + 1, intervals[i][0] - 1);
    }

    return 0;
}
