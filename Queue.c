// Queue.c ... implementation of Queue ADT
// Written by  Fiona Lin

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Path.h"
#include "Queue.h"

typedef struct QueueNode {
	Path value;
	struct QueueNode *next;
} QueueNode;

typedef struct QueueRep {
	QueueNode *head;  // ptr to first node
	QueueNode *tail;  // ptr to last node
} QueueRep;


// create new empty Queue
Queue newQueue() {
	Queue q;
	q = malloc(sizeof(QueueRep));
	assert(q != NULL);
	q->head = NULL;
	q->tail = NULL;
	return q;
}

// free memory used by Queue
void dropQueue(Queue Q) {
	QueueNode *curr, *next;
	assert(Q != NULL);
	// free list nodes
	curr = Q->head;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	// free queue rep
	free(Q);
}
//
//void showQueue(Queue Q) {
//	QueueNode *curr;
//	assert(Q != NULL);
//	// free list nodes
//	curr = Q->head;
//	while (curr != NULL) {
//		PathShow(curr->value);
//		if (curr->next != NULL)
//		curr = curr->next;
//	}
//	printf("\n");
//}
//
// add item at end of Queue
void QueueJoin(Queue Q, Path it) {
	assert(Q != NULL);
	QueueNode *new = malloc(sizeof(QueueNode));
	assert(new != NULL);
	new->value = it;
	new->next = NULL;
	if (Q->head == NULL)
		Q->head = new;
	if (Q->tail != NULL)
		Q->tail->next = new;
	Q->tail = new;
}

// remove item from front of Queue
Path QueueLeave(Queue Q) {
	assert(Q != NULL);
	assert(Q->head != NULL);
	Path it = Q->head->value;
	QueueNode *old = Q->head;
	Q->head = old->next;
	if (Q->head == NULL)
		Q->tail = NULL;
	free(old);
	return it;
}

// check for no items
int QueueIsEmpty(Queue Q) {
	return (Q->head == NULL);
}

