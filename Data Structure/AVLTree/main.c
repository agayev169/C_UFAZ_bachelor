#include <stdio.h>
#include "AVLTree.h"

int main(int argc, char const *argv[]) {
    AVLTree *tree = NULL;
    printf("OK ");
    add(&tree, 20);
    printf("OK ");
    // printNode(tree);
    // printf("\n");
    // printf("DepthDiff: %d\n", getBalanced(&tree));
    add(&tree, 10);
    printf("OK ");
    // printf("DepthDiff: %d\n", getBalanced(&tree));
    add(&tree, 30);
    printf("OK ");
    // printf("DepthDiff: %d\n", getBalanced(&tree));
    add(&tree, 15);
    printf("OK ");
    // printf("DepthDiff: %d\n", getBalanced(&tree));
    add(&tree, 5);
    printf("DepthDiff: %d\n", getBalanced(&tree));
    printf("OK ");
    add(&tree, 0);
    printf("OK ");
    printf("DepthDiff: %d\n", getBalanced(&tree));
    // rightRotation(&tree);
    // printf("DepthDiff: %d\n", getBalanced(&tree));
    add(&tree, 12);
    printf("DepthDiff: %d\n", getBalanced(&tree));
    add(&tree, 11);
    // getAllBalanced(&tree);
    printf("DepthDiff: %d\n", getBalanced(&tree));
    // printf("DepthDiff-Right: %d\n", getBalanced(&(tree->right)));
    // rightRotation(&(tree->right));
    // leftRotation(&tree);
    // getAllBalanced(&tree);
    printNode(tree);
    printNode(tree->left);
    printNode(tree->right);
    printf("DepthDiff: %d\n", getBalanced(&tree));
    printf("DepthDiff-Left: %d\n", getBalanced(&(tree->left)));
    printf("DepthDiff-Right: %d\n", getBalanced(&(tree->right)));

    return 0;
}
