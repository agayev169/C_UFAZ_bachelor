#include <stdio.h>
#include <math.h>

typedef struct {
    int x;
    int y;
} Vector;

Vector findNext(Vector a, Vector b[], int bLength, int checkedP[]);
float distance(Vector a, Vector b);
int sort(Vector a);
Vector findMinV(Vector a[], int nbV, int tSort[], int type);
void move(Vector a[], int nbV, int tSort[], Vector minV, int type);
int gotPassengers(Vector t[], int nbT, Vector p[], int nbP);

int main(int argc, char const *argv[]) {
    int nbT;
    int nbP;
    int nbZ;
    scanf("%d", &nbT);
    Vector t[nbT];
    for (int i = 0; i < nbT; i++) {
        scanf("%d", &t[i].x);
        scanf("%d", &t[i].y);
    }

    scanf("%d", &nbP);
    Vector p[nbP];
    for (int i = 0; i < nbP; i++) {
        scanf("%d", &p[i].x);
        scanf("%d", &p[i].y);
    }

    // scanf("%d", &nbZ);
    // Vector z[nbZ];
    // for (int i = 0; i < nbZ; i++) {
    //     scanf("%d", &z[i].x);
    //     scanf("%d", &z[i].y);
    // }

    int checkedP[nbP];
    Vector tp[nbT];
    int tSort[nbT];
    for (int i = 0; i < nbP; i++) checkedP[i] = 0;
    for (int i = 0; i < nbT; i++) {
        tp[i] = findNext(t[i], p, nbP, checkedP);
        tSort[i] = sort(tp[i]);
        printf("\n");
    }

    while (!gotPassengers(t, nbT, p, nbP)) {
        Vector minV[8];
        for (int i = 0; i < nbT; i++) minV[i].x = minV[i].y = 0;
        for (int i = 0; i < 8; i++) minV[i] = findMinV(tp, nbT, tSort, i);

        for (int i = 0; i < 8; i++) move(t, nbT, tSort, minV[i], i);
        for (int i = 0; i < nbT; i++) printf("Taxi[%d]: %d, %d\n", i, t[i].x, t[i].y);


        for (int i = 0; i < nbT; i++) printf("%d, %d; %d\n", tp[i].x, tp[i].y, tSort[i]);
        printf("\n");
        for (int i = 0; i < 8; i++) printf("minV[%d]: %d, %d\n", i, minV[i].x, minV[i].y);
        for (int i = 0; i < nbT; i++) {
            tSort[i] = sort(tp[i]);
        }
    }

    // Vector t = {0, 0};
    // Vector t2 = {0, 0};
    // Vector p[] = {{1, 1}, {2, 2}, {-1, 0}, {0, 1}};
    // int checkedP[] = {0, 0, 0, 0};
    // Vector ab = findNext(t, p, 4, checkedP);
    // printf("%d, %d\n", ab.x, ab.y);
    // ab = findNext(t2, p, 4, checkedP);
    // printf("%d, %d\n", ab.x, ab.y);

    return 0;
}

Vector findNext(Vector a, Vector b[], int bLength, int checkedP[]) {
    // printf("bLength: %d\n", bLength);
    float minDist = 999999;
    int index = -1;
    for (int i = 0; i < bLength; i++) {
        float dist = distance(a, b[i]);
        // printf("dist[%d]: %f\n", i, dist);
        if (dist < minDist && !checkedP[i]) {
            index = i;
            minDist = dist;
        }
    }
    Vector ab = {0, 0};
    if (index != -1) {
        ab.x = b[index].x - a.x;
        ab.y = b[index].y - a.y;
        checkedP[index] = 1;
    }
    // printf("index: %d\n", index);
    // printf("minDist: %f\n", minDist);
    return ab;
}

float distance(Vector a, Vector b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int sort(Vector a) {
    if (!a.x && a.y > 0) return 0;
    if (a.x > 0 && a.y > 0) return 1;
    if (a.x > 0 && !a.y) return 2;
    if (a.x > 0 && a.y < 0) return 3;
    if (!a.x && a.y < 0) return 4;
    if (a.x < 0 && a.y < 0) return 5;
    if (a.x < 0 && !a.y) return 6;
    if (a.x < 0 && a.y < 0) return 7;
    return -1;
}

Vector findMinV(Vector a[], int nbV, int tSort[], int type) {
    Vector minV = {0, 0};
    for (int i = 0; i < nbV; i++) {
        // printf("tSort[%d]: %d, a[%d].x: %d, a[%d].y: %d\n", i, tSort[i], i, a[i].x, i, a[i].y);
        if (tSort[i] == type) {
            if (minV.x == 0 && minV.y == 0) {
                minV.x = a[i].x;
                minV.y = a[i].y;
            } else if (type == 0 && minV.y > a[i].y)
                minV.y = a[i].y;
            else if (type == 1 && minV.y > a[i].y && minV.x > a[i].x) {
                minV.x = a[i].x;
                minV.y = a[i].y;
            } else if (type == 2 && minV.x > a[i].x)
                minV.x = a[i].x;
            else if (type == 3 && minV.x > a[i].x && minV.y < a[i].y) {
                minV.x = a[i].x;
                minV.y = a[i].y;
            } else if (type == 4 && minV.y < a[i].y)
                minV.y = a[i].y;
            else if (type == 5 && minV.y < a[i].y && minV.x < a[i].x) {
                minV.x = a[i].x;
                minV.y = a[i].y;
            } else if (type == 6 && minV.x < a[i].x)
                minV.x = a[i].x;
            else if (type == 7 && minV.x < a[i].x && minV.y > a[i].y) {
                minV.x = a[i].x;
                minV.y = a[i].y;
            }
        }
    }
    return minV;
}

void move(Vector a[], int nbV, int tSort[], Vector minV, int type) {
    for (int i = 0; i < nbV; i++) {
        if (tSort[i] == type) {
            a[i].x += minV.x;
            a[i].y += minV.y;
            printf("MOVE %d %d %d\n", i, minV.x, minV.y);
        }
    }
}

int gotPassengers(Vector t[], int nbT, Vector p[], int nbP) {
    for (int i = 0; i < nbT; i++) {
        int got = 0;
        for (int j = 0; j < nbP; j++) {
            if (t[i].x == p[i].x && t[i].y == p[i].y) got = 1;
        }
        if (!got) return 0;
    }
    return 1;
}
