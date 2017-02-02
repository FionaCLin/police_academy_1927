#include <stdlib.h>

#include "HItem.h"

HItem newHItem(Key k,int v){
    HItem i = malloc(sizeof(struct record));
    assert(i != NULL);
    i->weight = k;
    i->vertex= v;
    return i;
}
