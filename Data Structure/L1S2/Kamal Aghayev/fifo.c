/***************************************/
/*** Creating an "intelligent" queue ***/
/***************************************/

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"
#include "BSTree.h"


// int main(){
//   int n,m;
//   SFifo myFifo;
//
//   printf("Enter a queue size: ");scanf("%d",&n);
//   if (constructFifo(&myFifo,n)){
//     fprintf(stderr,"Error creating the queue\n");
//     return 1;
//   }
//
//   printf("Enqueue numbers (dequeue with -2, quit with -1)\n");
//   while (n!=-1){
//     scanf("%d",&n);
//     if (n==-1) break;
//     if (n==-2) {
//       m=deQueue(&myFifo);
//       if (m==-1) {
//         fprintf(stderr,"Dequeueing from empty queue!!!\n");
//         exit(1);
//       }
//       printf("Value %d dequeued\n",m);
//       printQueue(&myFifo);
//       continue;
//     }
//     if (enQueue(&myFifo,n)==-2){
//         fprintf(stderr,"enQueueing in full queue!!!\n");
//         exit(2);
//       }
//     printQueue(&myFifo);
//   }
//
//   destructFifo(&myFifo);
//   return 0;
// }
//-----------------------------------------------------------------------
void loadLevel(SFifo *p, BSNode *tree, int level) {
    if (tree != NULL) {
        if (level == 1) enQueue(p, tree);
        else if (level > 1) {
            loadLevel(p, tree->left, level-1);
            loadLevel(p, tree->right, level-1);
        }
    }
}


void loadTree(SFifo *p, BSNode *tree) {
    int n = treeDepth(tree);
    for (int i = 1; i <= n; i++) {
        loadLevel(p, tree, i);
    }
}


//-----------------------------------------------------------------------
int enQueue(SFifo *p, BSNode* n){
  BSNode* *pTemp, **pTemp2, *i;
  if (p->iEnQueue==p->iDeQueue){ // enlarge queue
    if (!(pTemp=(BSNode**)calloc(p->nSize+3,sizeof(BSNode*)))) {
      fprintf(stderr,"Memory Allocation Error");
      return 1;
    }
    for(int i=0;i<p->nSize;i++) // copy all the elements of pFifo
      pTemp[i]=p->pFifo[(p->iDeQueue+i)%p->nSize];
    p->iDeQueue=0;p->iEnQueue=p->nSize;
    pTemp2=p->pFifo; p->pFifo=pTemp; free(pTemp2); // update array
    p->nSize+=3;
  }

  p->pFifo[p->iEnQueue]=n;
  if (p->iDeQueue==-1) p->iDeQueue=p->iEnQueue;
  p->iEnQueue=(p->iEnQueue+1)%p->nSize;
  return 0;
}
//-----------------------------------------------------------------------
int printQueue(SFifo *p){
  printf("Fifo = [");
  for (int i=0;i<p->nSize;i++) {
      if (p->pFifo[i])
        printNode(p->pFifo[i]);

  }//printf("%d, ",p->pFifo[i]->val);
  printf("\b\b]\n");
  printf("Value of iEnQueue: %d, iDeQueue: %d\n", p->iEnQueue, p->iDeQueue);
  return 0;
 }
//-----------------------------------------------------------------------
BSNode* deQueue(SFifo *p){
  BSNode* n;
  int nFreeSpace; // n is the value; nFreeSpace empty space between EnQueue and DeQueue
  if (p->iDeQueue==-1) return NULL; // the Fifo is empty // Exit function
  n=p->pFifo[p->iDeQueue]; // else get the value n
  p->iDeQueue=(p->iDeQueue+1)%p->nSize; // Move the DeQueue
  if (p->iDeQueue>p->iEnQueue) nFreeSpace=p->iDeQueue-p->iEnQueue; // Calculate space Case 1
  else nFreeSpace=p->iDeQueue-p->iEnQueue+p->nSize; // Calculate Space Case 2
  printf("Free space=%d\n",nFreeSpace); // Print the space

if(nFreeSpace>3 && p->nSize>5){ // Shrink Fifo // Decrease the size of queue
	BSNode **pTemp, **pTemp2;
    if (!(pTemp=(BSNode**)calloc(p->nSize-3,sizeof(BSNode*)))) {
      fprintf(stderr,"Memory Allocation Error");
      return NULL;
    }
    for(int i=0;i<p->nSize-3;i++) // copy all the elements of pFifo
      pTemp[i]=p->pFifo[(p->iDeQueue+i)%p->nSize];
    p->nSize-=3;
    p->iDeQueue=0;p->iEnQueue=p->nSize-1;
    pTemp2=p->pFifo; p->pFifo=pTemp; free(pTemp2); // update array
  }

  if (p->iDeQueue==p->iEnQueue)p->iDeQueue=-1; // if Moving the DeQueue cause Empty Fifo
  return n; // Return the DeQueued Value.
}
//-----------------------------------------------------------------------
int constructFifo(SFifo *p, int n){
  if (!(p->pFifo=(BSNode* *)calloc(n,sizeof(BSNode*)))) {
    fprintf(stderr,"Memory Allocation Error");
    return 1;
  }
  p->nSize=n;
  p->iEnQueue=0;
  p->iDeQueue=-1;
  return 0;
}
//-----------------------------------------------------------------------
int destructFifo(SFifo *p){
free(p->pFifo);
return 0;
}
