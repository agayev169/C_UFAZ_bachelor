#include "AVLTree.h"
#include <stdlib.h>
#include <stdio.h>

void add(AVLTree **tree, int val) {
	int next;
	AVLTree *i, *pSent;
	for (i = *tree; i != NULL;) {
		pSent = i;
		if (i->val > val) {
			i = i->left;
			next = 0;
		} else {
			i = i->right;
			next = 1;
		}
	}

	AVLTree *newN;
	if (!(newN = (AVLTree*)malloc(sizeof(AVLTree)))) {
		fprintf(stderr, "Error in add function! No space to create a node!\n");
		exit(1);
	}
	newN->left = NULL;
	newN->right = NULL;
	newN->val = val;

	if (*tree == i) {
        *tree = newN;
    }
	else {
		if (next == 0) pSent->left = newN;
		else pSent->right = newN;
	}

    getAllBalanced(tree);
    // while ((*tree)->depthDiff < -1 || (*tree)->depthDiff > 1) {
        // printf("While loop\n");
        if ((*tree)->depthDiff < -1) {
            if ((*tree)->left->depthDiff < -1) rightRotation(tree);
            else {
                leftRotation(&((*tree)->left));
                rightRotation(tree);
            }
        } else {
            if ((*tree)->right->depthDiff > 1) leftRotation(tree);
            else {
                rightRotation(&((*tree)->right));
                leftRotation(tree);
            }
        }
        getAllBalanced(tree);
    // }
}

void printNode(AVLTree *tree) {
    if (!tree) {
        fprintf(stderr, "Error in printing function! Null pointer exception\n");
        return;
    }
    printf("%d\t", tree->val);
}

int height(AVLTree *tree) {
    if (tree) {
        int left = height(tree->left);
        int right = height(tree->right);
        return left > right ? left + 1 : right + 1;
    }
    return 0;
}

int getBalanced(AVLTree **tree) {
    if (!tree) return 0;
    int left = height((*tree)->left);
	int right = height((*tree)->right);
	(*tree)->depthDiff = right - left;
    return (*tree)->depthDiff;
}

void getAllBalanced(AVLTree **tree) {
    if (!*tree) return;
    int left = height((*tree)->left);
	int right = height((*tree)->right);
	(*tree)->depthDiff = right - left;
    getAllBalanced(&((*tree)->left));
    getAllBalanced(&((*tree)->right));
}

void rightRotation(AVLTree **tree) {
    AVLTree *left = (*tree)->left;
    // AVLTree *temp = *tree;
    // *tree = (*tree)->left;
    // temp->left = (*tree)->right;
    // (*tree)->right = temp;
}

void leftRotation(AVLTree **tree) {
    AVLTree *right = (*tree)->right;
    AVLTree *temp = (*tree);
    (*tree) = (*tree)->right;
    temp->right = (*tree)->left;
    (*tree)->left = temp;
}
