//A complex Path with a key and a value
#ifndef QITEM_H
#define QITEM_H
#include <assert.h>

typedef struct record * Path;
typedef int Key;    //non-negative key
struct record{
    int vertex;    //vertex id
    Key turn;       //turns
    int stamina;   //stamina end of the path
    Path prev;
};

#define NULLitem NULL  //This indicates no item
#define hops(A) ((A)->turn)
#define prev(A) ((A)->prev)
#define stamina(A) ((A)->stamina)
#define dest(A) ((A)->vertex)
#define less(A,B) (((A)->turn) < ((B)->turn))
#define greater(A,B) (((A)->turn) > ((B)->turn))
#define equal(A,B) (((A)->turn) == ((B)->turn))
//#define PathShow(i) printf("{%d - %d -> %d stamina %d}", dest(i), hops(i), destination(prev(i)), stamina(i))

// make new item to join the queue
Path newPath(int turns, int v, int stamina, Path prev);
int numPaths(Path p);
Path PathCopy(Path it);
void freePath(Path p);
#endif
