#include <stdio.h>

void findRectangleCentre(int vertex[8], int *x, int *y) {
    *x = vertex[0] - vertex[2];
    *y = vertex[1] - vertex[5];
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);
    int shape[n];
    int vertex[n][8];
    int res = 1;
    for (int i = 0; i < n; i++) {
        // printf("Iteration # %d\n", i);
        scanf("%d", &shape[i]);
        if (0 == shape[i]) {
            for (int j = 0; j < 3; j++) {
                scanf("%d", &vertex[i][j]);
            }
        } else {
            for (int j = 0; j < 8; j++) {
                scanf("%d", &vertex[i][j]);
            }
        }
    }

    if (n < 3) {
        printf("YES\n");
        return 0;
    }
    else {
        int k, b;
        if (shape[0] == 0) {
            if (shape[1] == 0) {
                k = (vertex[1][2] - vertex[0][2]) / (vertex[1][1] - vertex[0][1]);
                b = vertex[0][2] - k * vertex[0][1];
            } else {
                int x, y;
                findRectangleCentre(vertex[1], &x, &y);
                k = (y - vertex[0][2]) / (x - vertex[0][1]);
                b = y - k * x;
            }
        } else {
            int x, y;
            findRectangleCentre(vertex[0], &x, &y);
            if (shape[1] == 0) {
                k = (vertex[1][2] - y) / (vertex[1][1] - x);
                b = y - k * x;
            } else {
                int x2, y2;
                k = (y2 - y) / (x2 - x);
                b = y - k * x;
            }
        }
        for (int i = 2; i < n; i++) {
            if (shape[i] == 0) {
                if (!(k * vertex[i][1] + b == vertex[i][2])) {
                    res = 0;
                    break;
                }
            } else {
                int x, y;
                findRectangleCentre(vertex[i], &x, &y);
                if (!(k * x + b == y)) {
                    res = 0;
                    break;
                }
            }
        }
    }

    if (res == 1) printf("YES\n");
    else printf("NO\n");

    return 0;
}
