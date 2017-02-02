// A priority Queue Min Heap ADT interface
#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include "HItem.h"

typedef struct pqRep * MinHeap;

// Core operations
// set up empty min heap
MinHeap newHeap(int size);

// insert a record(vertex & weight) to heap
void insertHeap(MinHeap q, HItem it);

//
void decreaseWeight(MinHeap q, int v, Key k);

// delete from the root
HItem delMin(MinHeap q);

// check whether min heap is empty
int isEmpty(MinHeap q);

#endif
