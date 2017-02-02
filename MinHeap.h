// A priority Queue Min Heap ADT interface
#ifndef MIN_HEAP_H
#define MIN_HEAP_H
typedef struct pqRep * MinHeap;

#include "HItem.h"

// Core operations
MinHeap newMinHeap(int size);

void insert(MinHeap q, HItem it);
void decreaseWeight(MinHeap q, int v, Key k);
HItem delMin(MinHeap q);

// Useful operations
int isEmpty(MinHeap q);


#endif
