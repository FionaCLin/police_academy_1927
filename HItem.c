#include <stdlib.h>

#include "HItem.h"

HItem newHItem(Key k,int v){
    HItem i = malloc(sizeof(struct record));
    assert(i != NULL);
    i->keyVal = k;
    i->value = v;
    return i;
}
