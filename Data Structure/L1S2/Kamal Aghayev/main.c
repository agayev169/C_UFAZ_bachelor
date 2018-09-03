#include <stdio.h>
#include "BSTree.h"
#include "fifo.h"

int main(int argc, char const *argv[]) {
    BSNode *tree = NULL;
    tree = add(tree, 25);
    tree = add(tree, 15);
    tree = add(tree, 35);

    SFifo fifo;
    constructFifo(&fifo,5);
    loadTree(&fifo, tree);
    printQueue(&fifo);

    return 0;
}
