#include <stdio.h>
#include <stdlib.h>
#include "lzw.h"

int main() {
    LZWList *list = NULL;
    char *str = "si ton tonton tond mon tonton";
    char *rFileName = "test.txt";
    char *wrFileName = "write.txt";

    // printList(list);
    compress(rFileName, wrFileName, &list);

    printList(list);
    printf("\n");

    return 0;
}