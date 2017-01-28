//Queue.h; // interface to Queue ADT
// Written by John Shepherd, March 2013

#ifndef QUEUE_H
#define QUEUE_H

#include "Item.h"

typedef struct QueueRep *Queue;

// create new empty queue
Queue newQueue();

// free memory used by queue
void dropQueue(Queue);

// display as 3 > 5 > 4 > ...
void showQueue(Queue);

// add item on queue
void QueueJoin(Queue,Item);

// remove item from queue
Item QueueLeave(Queue);

// check for no items
int QueueIsEmpty(Queue);
#endif
