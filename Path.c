// Path.c ... implementation of Path ADT
// Written by Fiona Lin, Feb 4 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Path.h"

Path PathCopy(Path it) {
    Path copy = newPath(it->turn, it->vertex, it->stamina, it->prev);
    return copy;
}

Path newPath(Key turns, int v, int stamina, Path prev){
    Path i = malloc(sizeof(struct record));
    assert(i != NULL);
    i->turn = turns;
    i->vertex= v;
    i->stamina = stamina;
    i->prev = prev;
    return i;
}

int numPaths(Path p) {
    Path cur = p;
    int c = 0;
    while (cur != NULL) {
        c++;
        cur = cur -> prev;
    }
    return c;
}

void freePath(Path p) {
    Path tem = NULL;
    Path cur = NULL;
    while (p != NULL) {
        for (cur = p; cur -> prev != NULL; cur = cur -> prev);
        tem = cur;
        cur = NULL;
        free(tem);
    }
}



