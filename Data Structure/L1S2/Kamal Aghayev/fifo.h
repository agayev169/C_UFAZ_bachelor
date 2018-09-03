#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdio.h>
#include <stdlib.h>
#include "BSTree.h"

typedef struct Fifo {
  int iEnQueue, iDeQueue, nSize;
  BSNode** pFifo;
} SFifo;

int constructFifo(SFifo *p, int n); // signature of the function
int enQueue(SFifo *p, BSNode* n);
BSNode* deQueue(SFifo *p);
int destructFifo(SFifo *p);
int printQueue(SFifo *p);
void loadLevel(SFifo *p, BSNode *tree, int level);
void loadTree(SFifo *p, BSNode *tree);

#endif
