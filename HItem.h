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
#define key(A) ((A)->weight)
#define value(A) ((A)->vertex)
#define less(A,B) (((A)->weight) < ((B)->weight))
#define greater(A,B) (((A)->weight) > ((B)->weight))
#define lessEq(A,B) (((A)->weight) <= ((B)->weight))

HItem newHItem(int w,int v);

#endif
