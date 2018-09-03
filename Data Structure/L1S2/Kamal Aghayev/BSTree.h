#ifndef __BSTREE_H__
#define __BSTREE_H__

#include<stdio.h>
#include<stdlib.h>
//#include<math.h>
//#define DIGITS 2

typedef struct Node{
int val;
struct Node *left, *right;
}BSNode;

BSNode *constructTree(int n);
BSNode *add(BSNode *pTree, int n);
void printNode(BSNode *pTree);
void treeTraverseA(BSNode *pTree);
void treeTraverseD(BSNode *pTree);
int treeNodeNumber(BSNode *pTree, int *d);
int treeDepth(BSNode *pTree);
void treePrintLevel(BSNode *pTree, int level);
void treePrintLevels(BSNode *root, int *d);
int BSearch(BSNode *pTree, int n);


#endif
