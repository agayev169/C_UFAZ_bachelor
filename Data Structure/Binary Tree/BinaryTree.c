#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BinaryTree.h"

int add(BinaryTreeInt **tree, int val) {
	int next;
	BinaryTreeInt *i, *pSent;
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

	BinaryTreeInt *newN;
	if (!(newN = (BinaryTreeInt*)malloc(sizeof(BinaryTreeInt)))) {
		fprintf(stderr, "Error in add function! No space to create a node!\n");
		exit(1);
	}
	newN->left = NULL;
	newN->right = NULL;
	newN->val = val;

	if (*tree == i) *tree = newN;
	else {
		if (next == 0) pSent->left = newN;
		else pSent->right = newN;
	}

	int left = treeDepth((*tree)->left);
	int right = treeDepth((*tree)->right);
	// printf("Left: %d\n", left);
	// printf("Right: %d\n", right);

	(*tree)->depthDiff = abs(left - right);

	return 0;
}

int printNode(BinaryTreeInt *tree) {
    if (!tree) return 1;
    printf("%d\t", tree->val);
    return 0;
}

int printTreeAsc(BinaryTreeInt *tree) {
	if (!tree) return 0;
	printTreeAsc(tree->left);
	printNode(tree);
	printTreeAsc(tree->right);
	return 0;
}

int printTreeDes(BinaryTreeInt *tree) {
	if (!tree) return 0;
	printTreeDes(tree->right);
	printNode(tree);
	printTreeDes(tree->left);
	return 0;
}

int printAsTree(BinaryTreeInt *tree) {
	int depth = treeDepth(tree) + 1;
	// printf("%d\n", depth);
	for (int i = 1; i <= depth; i++) {
		int spaces = (depth - i + 1) * (depth - i + 1) * 2;
		printLevel2(tree, i, spaces);
		printf("\n");
		if (i == depth) break;
		int slashes = pow(2, i);
		for (int i = 0; i < slashes; i++) {
			for (int j = 0; j < spaces / 2 + spaces / 4; j++) {
				printf(" ");
			}
			i % 2 == 0 ? printf("/") : printf("\\");
			if (i % 2 == 0) {
				for (int j = 0; j < spaces / 2 - spaces / 4; j++) {
					printf(" ");
				}
			}
		}
		printf("\n");
	}
	return 0;
}

int printNode2(BinaryTreeInt *tree, int spaces) {
	if (!tree)
		return 1;
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
    printf("%d", tree->val);
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
    return 0;
}

int printLevel2(BinaryTreeInt *tree, int level, int spaces) {
	if (!tree) {
		for (int i = 0; i < spaces * 2 + 2; i++) {
			printf(" ");
		}
		return 1;
	}
	level--;
	if (level == 0) {
		printNode2(tree, spaces);
	} else {
		printLevel2(tree->left, level, spaces);
		printLevel2(tree->right, level, spaces);
	}
	return 0;
}

int treeNodeNumber(BinaryTreeInt *tree, int *d) {
	if (!tree) return 0;
	(*d)++;
	treeNodeNumber(tree->left, d);
	treeNodeNumber(tree->right, d);
	return 0;
}

int search(BinaryTreeInt *tree, int n) {
	if (!tree) return 1;
	if (tree->val == n) return 0;
	if (n < tree->val) if (search(tree->left, n) == 0) return 0;
	else if (search(tree->right, n) == 0) return 0;
	return 1;
}

int printLevel(BinaryTreeInt *tree, int level) {
	if (!tree) return 1;
	level--;
	if (level == 0) {
		printNode(tree);
	} else {
		printLevel(tree->left, level);
		printLevel(tree->right, level);
	}
	return 0;
}

int printLevels(BinaryTreeInt *tree) {
	int level = 1;
	int n = 0;
	treeDepth(tree);
	while (level <= n) {
		printLevel(tree, level);
		printf("\n");
		level++;
	}
	return 0;
}

int treeDepth(BinaryTreeInt *tree) {
	if (tree) {
		int left = treeDepth(tree->left);
		int right = treeDepth(tree->right);
		return left > right ? left + 1 : right + 1;
	}
	return 0;
}

int treeDepth2(BinaryTreeInt *tree, int *d, int level) {
	if (!tree) return level;
	level++;
	if (treeDepth2(tree->left, d, level) > (*d)) (*d) = level;
	if (treeDepth2(tree->right, d, level) > (*d)) (*d) = level;
	return level;
}

int delete(BinaryTreeInt *tree, int x) {
	if (tree != NULL) {
		if (tree->val < x) delete(tree->right, x);
		else if (tree->val > x) delete(tree->left, x);
		else {
			if (tree->left == NULL && tree->right == NULL) {
				// tree = NULL;
				free(tree);
			} else if (tree->left == NULL) {
				tree = tree->right;
			} else if (tree->right == NULL) {
				tree = tree->left;
			} else {
				BinaryTreeInt *temp = successor(tree);
				tree->val = temp->val;
				delete(tree->right, temp->val);
			}
		}
		return 0;
	}
}

BinaryTreeInt *successor(BinaryTreeInt *tree) {
	BinaryTreeInt *temp = tree->right;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return temp;
}
