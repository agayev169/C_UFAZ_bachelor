#include <stdio.h>

int main(int argc, char const *argv[]) {
    int h, m;
    scanf("%d %d", &h, &m);
    h = (12 - h) % 12;
    m = (60 - m) % 60;
    printf("%d %d\n", h, m);

    return 0;
}
