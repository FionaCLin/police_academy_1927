// Path.c ... implementation of Path ADT
// Written by Fiona Lin, Feb 4 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Path.h"

Path PathCopy(Path it) {
    Path copy = NULL;
    if (it != NULL && it->prev == NULL) {
        copy = newPath(it->vertex, it->turn, it->stamina, NULL);
    } else {
        copy = PathCopy(it->prev);
        copy = newPath(it->vertex, it->turn, it->stamina, copy);
    }

    return copy;
}

Path newPath(int v, Key turns, int stamina, Path prev){
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
    cur = p;
    while (cur != NULL) {
        tem = cur;
        cur = cur -> prev;
        free(tem);
    }
}