#include"HT.h"
#include"LL.h"
//-----------------------------------------------
HLNode *readList(LLNode *ll){
    HLNode *hlList;// = (HLNode*) malloc(sizeof(HLNode));
    while (ll) {
        HuffNode *newLeaf = (HuffNode*) malloc(sizeof(HuffNode));
        newLeaf->val = ll->nVal;
        newLeaf->ch = ll->ch;
        newLeaf->left = NULL;
        newLeaf->right = NULL;
        LLH_sorted_add(&hlList, newLeaf->val, newLeaf);
        ll = ll->pNext;
    }
    return hlList;
}
//-----------------------------------------------
int LLH_sorted_add(HLNode **ppList,int n, HuffNode *new){
    HLNode *pSent, *pCur;
    pSent=pCur=*ppList;
    while((pCur)&&(pCur->sum < n)){
        pSent=pCur;
        pCur=pCur->pNext;
    }
    if (pSent==pCur){
        *ppList=(HLNode*)malloc(sizeof(HLNode));
        (*ppList)->sum=n;
        (*ppList)->hTree=new;
        (*ppList)->pNext=pCur;
    } else{
        pSent->pNext=(HLNode*)malloc(sizeof(HLNode));
        (pSent->pNext)->sum=n;
        (pSent->pNext)->hTree=new;
        (pSent->pNext)->pNext=pCur;
    }
    return 0;
}
//-----------------------------------------------
HuffNode *buildTree(HLNode *myList){
    while (myList) {
        if (myList->pNext == NULL) {
            return myList->hTree;
        } else {
            HLNode *first  = myList; myList = myList->pNext;
            HLNode *second = myList; myList = myList->pNext;
            HuffNode *top = (HuffNode*) calloc(1, sizeof(HuffNode));
            top->val = first->sum + second->sum;
            top->left = first->hTree;
            top->right = second->hTree;
            top->ch = '$';
            LLH_sorted_add(&myList, top->val, top);
            HL_Print(myList);
        }
    }
    return NULL;
}
//-----------------------------------------------
void printHTree(HuffNode *hTree){
    if (hTree == NULL) {
        return;
    }
    printHTree(hTree->left);
    printf("[%d, %c]  ", hTree->val, hTree->ch);
    printHTree(hTree->right);
}
//-----------------------------------------------
int HL_Print(HLNode *pList){
    if (pList == NULL) {
        printf("pList-/\n");
        return 1;
    }
    printf("pList->[%d, %c]->", pList->sum, pList->hTree->ch);
    while (pList->pNext) {
        pList = pList->pNext;
        printf("[%d, %c]->", pList->sum, pList->hTree->ch);
    }
    printf("//\n");
    return 0;
}
//-----------------------------------------------
void printChar(HuffNode *hTree, char *str, int count) {
    if (hTree->left == NULL && hTree->right == NULL) {
        printf("%c : ", hTree->ch);
        for (int i = 0; i < count; i++) {
            printf("%c", str[i]);
        }
        printf("\n");
    } else {
        // printf("Left: %p, Right: %p", hTree->left, hTree->right);
        // printf("%s, count: %d\n", str, count);
        if (hTree->left) {
            str[count] = '0';
            printChar(hTree->left, str, count + 1);
        }
        if (hTree->right) {
            str[count] = '1';
            printChar(hTree->right, str, count + 1);
        }
    }
}
//-----------------------------------------------
int findLetter(HuffNode *hTree, char *str, char l, int count, int *size) {
    if (hTree->left == NULL && hTree->right == NULL) {
        if (hTree->ch == l) {
            *size = count;
            return 0;
        }
        return 1;
    } else {
        if (hTree->left) {
            str[count] = '0';
            if (findLetter(hTree->left, str, l, count + 1, size) == 0) return 0;
        }
        if (hTree->right) {
            str[count] = '1';
            if (findLetter(hTree->right, str, l, count + 1, size) == 0) return 0;
        }
    }
    return 1;
}