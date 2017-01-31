// A priority Queue Min Heap ADT interface
#ifndef MIN_HEAP_H
#define MIN_HEAP_H
typedef struct pqRep * MinHeap;

// Core operations
MinHeap newMinHeap(int size);
void insert(MinHeap q, HItem it);
HItem delMin(MinHeap q);

// Useful operations
int isEmpty(MinHeap q);
void delete(MinHeap q, Key k);

void decreaseWeight(MinHeap q, int v, Key k);
#endif
