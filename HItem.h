//A complex HItem with a key and a value
#ifndef HITEM_H
#define HITEM_H
#include <assert.h>

typedef int Key;    //non-negative key
struct record{
    Key weight;    //distance/weight
    int vertex;    //vertex id
};
typedef struct record * HItem;

#define NULLitem NULL  //This indicates no item
#define key(A) ((A)->keyVal)
#define value(A) ((A)->value)
#define less(A,B) (((A)->keyVal) < ((B)->keyVal))
#define greater(A,B) (((A)->keyVal) > ((B)->keyVal))
#define lessEq(A,B) (((A)->keyVal) <= ((B)->keyVal))

HItem newHItem(int w,int v);

#endif
