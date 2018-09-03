#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeInt {
    int val;
    struct BinaryTreeInt *left;
    struct BinaryTreeInt *right;
    int depthDiff;
} BinaryTreeInt;

int add(BinaryTreeInt **tree, int val);
int printNode(BinaryTreeInt *tree);
int printTreeAsc(BinaryTreeInt *tree);
int printTreeDes(BinaryTreeInt *tree);
int treeNodeNumber(BinaryTreeInt *tree, int *d);
int search(BinaryTreeInt *tree, int n);
int printLevel(BinaryTreeInt *tree, int n);
int printLevels(BinaryTreeInt *tree);
int treeDepth(BinaryTreeInt *tree);
int treeDepth2(BinaryTreeInt *tree, int *d, int level);
int printAsTree(BinaryTreeInt *tree);
int printNode2(BinaryTreeInt *tree, int spaces);
int printLevel2(BinaryTreeInt *tree, int level, int spaces);
int delete(BinaryTreeInt *tree, int x);
BinaryTreeInt *successor(BinaryTreeInt *tree);

#endif
