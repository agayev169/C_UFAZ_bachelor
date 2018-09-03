#ifndef _AVLTREE_H_
#define _AVLTREE_H_

typedef struct AVLTree{
    int val;
    struct AVLTree *left;
    struct AVLTree *right;
    int depthDiff;
} AVLTree;

void add(AVLTree **tree, int val);
void leftRotation(AVLTree **tree);
void rightRotation(AVLTree **tree);
void printNode(AVLTree *tree);
int height(AVLTree *tree);
int getBalanced(AVLTree **tree);
void getAllBalanced(AVLTree **tree);

#endif
