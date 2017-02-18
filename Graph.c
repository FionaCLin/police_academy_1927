/*
   Graph.c
   */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "Queue.h"
#include "Path.h"
#include "Graph.h"

#define MAXITEMS 500

struct graphRep {
    int nv;
    int ne;
    int thief;
    char *informants;
    char ** names;
    int ** edges;
};


static int validE(Graph g, Edge e) {
    return (e.v >= 0 && e.v < g->nv && e.w >= 0 && e.w < g->nv) &&
        (e.v != e.w) && e.weight >= 0;
}
static int validV(Graph g, Vertex v) {
    return (v >= 0 && v < g->nv);
}

char * hasInformant(Graph map, int city) {
    if (map == NULL) return 0;
    return (map->informants[city] == 'i')? "*" : "";
}

char * getCityName(Graph map, int city) {
    if (map == NULL) return NULL;
    return map->names[city];
}

void setThief(Graph map, Vertex city) {
    map->thief = city;
}

Vertex getThief(Graph map) {
    return map->thief;
}

// Create an edge from v to w
Edge mkEdge(Vertex v, Vertex w, int weight) {
    Edge e = {NO_EDGE, NO_EDGE, NO_EDGE};
    if (v >= 0 && w >= 0 && weight >=0) {
        e.v = v;
        e.w = w;
        e.weight = weight;
    } else if (weight < 0) {
        //    printf("Weight can't be nagtive.\n");
    } else {
        //    printf("Vertices can't be nagtive.\n");
    }
    return e;
}

//Initialise a new graph
Graph newGraph(int nV) {
    if (nV <= 0) {
        printf("Number of Vertices must be positive integer.\n");
        return NULL;
    }
    int i, j;
    Graph g = malloc(sizeof(struct graphRep));
    if (g == NULL) {
        printf("Unable to create Graph.\n");
        return NULL;
    }
    g->edges = malloc(sizeof(int *) * nV);
    if (g->edges == NULL) {
        printf("Unable to make Graph edges.\n");
        return NULL;
    }
    for (i = 0; i < nV; i++) {
        g->edges[i] = malloc(sizeof(int)* (i + 1));
        for (j = 0; j < i + 1; j++)
            g->edges[i][j] = NO_EDGE;
    }
    g->informants = malloc(sizeof(char) * nV);
    g->names = calloc(nV, sizeof(char *));
    g->nv = nV;
    g->ne = 0;
    return g;
}

void readCityInfo(Graph map, int index, char info, char * name) {
    if (map == NULL) {
        printf("Map is undefined yet\n");
        return;
    }
    map->informants[index] = info;
    map->names[index] = strdup(name);
}

//Insert an edge into a graph
//the edge must not be inserted if
//     the vertices are not valid
//     it would create a self loop
//     there already exists an edge between the vertices
void insertE(Graph g, Edge e) {
    int col, row;
    if (g == NULL) {
        printf("Invalid Graph.\n");
        return;
    }
    if (!validE(g, e)) {
        printf("Invalid edge {%d, %d, %d}.\n", e.v, e.w, e.weight);
        return;
    }
    row = e.v;
    col = e.w;
    if (e.v < e.w) {
        row = e.w;
        col = e.v;
    }
    if (g->edges[row][col] == NO_EDGE) {
        g->edges[row][col] = e.weight;
        g->ne++;
    }
}

//returns 1 if there is an edge from v to w
//returns 0 otherwise
int isAdjacent(Graph g, Vertex v, Vertex w) {
    int col, row;
    if (g == NULL) {
        printf("Invalid Graph.\n");
        return 0;
    }
    Edge e = {v, w};
    if (!validE(g, e)) {
        return 0;
    }
    row = e.v;
    col = e.w;
    if (e.v < e.w) {
        row = e.w;
        col = e.v;
    }
    if (g->edges[row][col] == NO_EDGE)
        return 0;
    return 1;
}

//returns the number of adjacent vertices
//and fills the adj array with the adjacent vertices
int adjacentVertices(Graph g, Vertex v, Vertex adj[]) {
    int i, nv = 0;
    if (g == NULL) {
        printf("Invalid Graph.\n");
        return 0;
    }
    if (!validV(g, v)) {
        printf("Invalid Vertex %d.\n", v);
        return 0;
    }
    if (adj == NULL) {
        printf("System runs out memory\n");
        return -1;
    }
    for (i = 0; i < v; i++)
        if (g->edges[v][i] != NO_EDGE) {
            adj[nv++]= i;
        }
    for (i = v + 1; i < g->nv; i++)
        if (g->edges[i][v] != NO_EDGE) {
            adj[nv++]= i;
        }
    return nv;
}

//returns the number of incident edges
//and fills the edges with incident edges
int incidentEdges(Graph g, Vertex v, Edge edges[]) {
    int i, ne = 0;
    if (g == NULL) {
        printf("Invalid Graph.\n");
        return 0;
    }
    if (!validV(g, v)) {
        printf("Invalid Vertex %d.\n", v);
        return 0;
    }
    if (edges == NULL) {
        printf("System runs out memory\n");
        return NO_EDGE;
    }
    for (i = 0; i < v; i++)
        if (g->edges[v][i] != NO_EDGE) {
            edges[ne++] = mkEdge(v, i, g->edges[v][i]);
        }
    for (i = v + 1; i < g->nv; i++)
        if (g->edges[i][v] != NO_EDGE) {
            edges[ne++] = mkEdge(v, i, g->edges[i][v]);
        }
    return ne;
}

void destroyGraph(Graph g) {
    if (g != NULL) {
        int i;
        if (g->edges != NULL) {
            for (i = 0; i < g->nv; i++)
                free(g->edges[i]);
        }
        free(g->edges);
        if (g->names != NULL) {
            for (i = 0; i < g->nv; i++)
                free(g->names[i]);
        }
        free(g->names);
        free(g->informants);
    }
    free(g);
}

//return the number of vertices in the graph
int numV(Graph g) {
    if (g == NULL) {
        printf("Invalid NULL Graph has no vertex.\n");
        return -1;
    }
    return g->nv;
}

//return the number of edges in the graph
int numE(Graph g) {
    if (g == NULL) {
        printf("Invalid NULL Graph has no edges.\n");
        return NO_EDGE;
    }
    return g->ne;
}

// returns the number of edges and fills the array of edges.
// nE is the max size of the es array
// The edges in the edges function should be in ascending order and not
// contain duplicates.
int edges(Edge es[], int nE, Graph g) {
    if (g == NULL) {
        printf("Invalid Graph.\n");
        return 0;
    }
    int v, w, count = 0;
    for (v = 1; v < g->nv; v++)
        for (w = 0; w < v; w++) {
            if (v < w) {
                int tmp = v;
                v = w;
                w = tmp;
            }
            if (g->edges[v][w] >= 0 && count < nE)
                es[count++] = mkEdge(v, w, g->edges[v][w]);
        }
    return count;
}

static int edgeWeight(Graph map, Vertex v, Vertex w) {
    int row = v;
    int col = w;
    if (v < w) {
        row = w;
        col = v;
    }
    return map->edges[row][col];
}

Edge getEdge(Graph g, Vertex v, Vertex w) {
    int row = v;
    int col = w;
    if (v < w) {
        row = w;
        col = v;
    }
    Edge e = {v, w, NO_EDGE};
    if (g != NULL) {
        e.weight =  g->edges[row][col];
    }
    return e;
}

//Display the graph
void show(Graph g) {
    assert(g != NULL);
    printf("V=%d, E=%d\n", numV(g), numE(g));
    int i, j;
    for (i = 0; i < numV(g); i++) {
        int nshown = 0;
        for (j = 0; j < numV(g); j++) {
            if (i == j) continue;
            if (isAdjacent(g, i, j)) {
                Edge e = getEdge(g, i, j);
                printf("%d-%d : %d ", e.v, e.w, e.weight);
                nshown++;
            }
        }
        if (nshown > 0) {
            printf("\n");
        }
    }
}

// dfSearch using Stack
//The initialisation of variables etc before we call the dfs function
int * dfSearch(Graph g, int maxStamina, int src, int *st, int *pre) {
    if (g == NULL) {
        printf("The graph g can't be NULL\n");
        return NULL;
    }
    int i, count = 0;
    int * path = calloc(numV(g), sizeof(int));
    for (i = 0; i < numV(g); i++) {
        path[i] = -1;
        st[i] = -1;
        pre[i] = -1;
    }
    //make a stack and push the 1st edge
    Stack stk = newStack();
    Edge ini = {src, -1, src};
    StackPush(stk, ini);
    while (!StackIsEmpty(stk)) {
        Edge e = StackPop(stk);
        if (pre[e.v] != -1) continue;
        path[count] = e.v;
        pre[e.v] = count++;
        st[e.v] = e.w;
        for (i = numV(g) - 1; i >= 0; i--) {
            int cost = edgeWeight(g, e.v, i);
            if ((cost <= maxStamina && cost != NO_EDGE) && (pre[i] == -1)) {
                Edge item = getEdge(g, i, e.v);
                StackPush(stk, item);
            }
        }
    }
    dropStack(stk);
    int j = 0, k = 0;
    int travelPath[MAXITEMS];
    travelPath[j] = path[j];
    for (i = 1; i < g->nv; ) {
        if (isAdjacent(g, travelPath[j], path[i])) {
            travelPath[++j] = path[i++];
        } else {
            if(path[i] == -1) {
                i++;
            } else {
                k = j;
                travelPath[++j] = st[travelPath[k]];
            }
        }
    }
    free(path);
    path = calloc(j + 1, sizeof(int));
    for (i = 0; i < j + 1; i++) {
        path[i] = travelPath[i];
    }
    return path;
}

Path lessTurnsPaths(Queue possiblePaths) {
    if (QueueIsEmpty(possiblePaths)) {
        return NULL;
    }
    Path res = QueueLeave(possiblePaths);
    Queue checked = newQueue();
    Path tem = NULL;
    while (!QueueIsEmpty(possiblePaths)) {
        Path cur = QueueLeave(possiblePaths);
        if (greater(res, cur)) {
            tem = res;
            res = cur;
            cur = tem;
        } else {
            if (equal(res, cur)) {
                if (stamina(res) < stamina(cur)) {
                    tem = res;
                    res = cur;
                    cur = tem;
                }
            }
        }
        QueueJoin(checked, cur);
    }
    while (!QueueIsEmpty(checked)) {
        Path cur = QueueLeave(checked);
        QueueJoin(possiblePaths, cur);
    }
    dropQueue(checked);
    return res;
}

// bfSearch using Queue
//The initialisation of variables etc before we call the dfs function
int * bfSearch(Graph g, int maxStamina, int curStamina, Vertex src, Vertex dest) {
    if (g == NULL) {
        printf("The graph g can't be NULL\n");
        return NULL;
    }
    int i, count = 0;

    int visit[g->nv];
    for (i = 0; i < numV(g); i++) visit[i] = NOT_YET;
    //make a queue and join the 1st edge
    Queue q = newQueue();
    Queue possiblePaths = newQueue();
    QueueJoin(q, newPath(src, 0, curStamina));
    while (!QueueIsEmpty(q)) {
        Path p = QueueLeave(q);
        if (visit[dest(p)] != NOT_YET) {
            freePath(p);
            continue;
        }
        if (dest(p) == dest)
            QueueJoin(possiblePaths, PathCopy(p));
        else visit[dest(p)] = count++;
        for (i = 0; i < numV(g); i++) {
            if (dest(p) == i || visit[i] != NOT_YET) continue;
            int cost = edgeWeight(g, dest(p), i);
            //when the edge weight greater than agent max stamina, it means no
            //possible path/edge in the map.
            if (cost > maxStamina || cost == NO_EDGE) continue;
            int turn = hops(p);
            int stamina = stamina(p);
            if (stamina(p) - cost < 0) {
                turn++;
                stamina = maxStamina;
            }
            Path pre = PathCopy(p);
            Path add = newPath(i, ++turn, stamina-cost);
            add->prev = pre;
            QueueJoin(q, add);
        }

        freePath(p);
    }
    dropQueue(q);
    Path routine = lessTurnsPaths(possiblePaths);
    while (!QueueIsEmpty(possiblePaths)) {
        Path pathToFree = QueueLeave(possiblePaths);
        freePath(pathToFree);
    }
    dropQueue(possiblePaths);
    int nPath = numPaths(routine);
    int *paths = NULL;
    if (routine != NULL) {
        paths =  malloc(sizeof(int) *nPath);
        if (nPath != 0) {
            paths[--nPath] = 1;
        } else {
            paths[--nPath] = -1;
        }
        Path cur = routine;
        while (cur -> prev != NULL) {
            paths[--nPath] = dest(cur);
            cur = cur->prev;
        }
    }
    freePath(routine);
    return paths;
}

