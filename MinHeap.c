// A min heap based implementation of a priority queue

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "MinHeap.h"

#define DEFAULT_MAX 100
#define NO_Item -1
#define PARENT(x) (x-1)/2
#define L_NODE(x) (2*x + 1)
#define R_NODE(x) (2*x + 2)

typedef struct pqRep *MinHeap;
struct pqRep {
    int nHItems;     // current number of items
    HItem *items;   // heap-array of HItems
    int size;     // maximum size of array
} ;

MinHeap newHeap(int size) {
    if(size < 0) {
        printf("Size is negative number, MinHeap set to default size %d", DEFAULT_MAX);
        size = DEFAULT_MAX;
    }
    MinHeap q = malloc(sizeof(struct pqRep));
    assert(q != NULL);
    q->items = malloc(sizeof(HItem) * size);
    assert(q->items != NULL);
    q->nHItems = NO_Item;
    q->size = size;
    return q;
}


// A local helper function to swap the item from index1 and index2 in the array
void swap(HItem a[],int index1,int index2){
    HItem tmp;
    tmp = a[index1];
    a[index1] = a[index2];
    a[index2] = tmp;
}

// Local function - not part of the interface
// Bottom up heapify
// force value at a[k] into correct position
void fixUp(HItem a[], int k) {
    while (k > 1 && greater(a[PARENT(k)],a[k])) {
        swap(a, k, PARENT(k));
        k = PARENT(k); // integer division
    }
}

// Top down heapify
// force value at a[k] into correct position
void fixDown(HItem a[], int k, int N) {
    while (2*k <= N) {
        //choose larger of two children
        int child = L_NODE(k);
        if (2*k < N && less(a[L_NODE(k)], a[R_NODE(k)]))
            child = R_NODE(k);
        if (!less(a[k], a[child]))
            swap(a, k, child);
        if(k != 0) k = 2 * k;
        else k = 1;
    }
}

// add a new item into the queue
void insertHeap(MinHeap q, HItem it) {
    assert(q != NULL && q->nHItems < q->size);
    q->nHItems++;
    q->items[q->nHItems] = it;
    fixUp(q->items, q->nHItems);
}

HItem delMin(MinHeap q) {
    assert(q != NULL && q->nHItems > 0);
    swap(q->items, 0, q->nHItems);
    q->nHItems--;
    fixDown(q->items, 0, q->nHItems);
    return q->items[q->nHItems + 1];
}


// Useful operations
int isEmpty(MinHeap q) {
    return (q->nHItems == 0);
}

void decreaseWeight(MinHeap q, int v, Key weight) {
    int i;
    for(i = 0; i < q->nHItems;i++){
        if(q->items[i]->vertex == v){
            q->items[i]->weight = weight;
            break;
        }
    }
    if(i <= q->nHItems)
        fixUp(q->items,i);
}

