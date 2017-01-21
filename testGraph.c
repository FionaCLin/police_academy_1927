/*
 *Task 0: Graph Black-Box Unit Testing 4 marks
 * You must write a testGraph.c that tests the functions defined in the
 * given Graph.h file. You must create assert(3)-based tests. We run
 * your testGraph.c code with our own working and broken graph
 * implementations to check they pass and fail the implementations
 * accordingly.
 *
 * Only use and test functions from the original Graph.h. Do not need to
 * submit tests for any additional functions you add to your graph when
 * you complete the other tasks of the assignment.
 *
 * You do not need assert(3)-based tests for the functions show or
 * destroyGraph.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "time.h"

#define MAXV 5
#define MAXE 10


void testNumV();
void testMkEdge();
void testNewGraph();
void testInsertE();
void testIsAdjacent();
void testAdjacentVertices();
void testIncidentEdges();
void testEdges();
void testNumE();



int eqE(Edge a, Edge b) {
    return (a.v == b.v && a.w == b.w)
        || (a.v=b.w && a.w == b.v);
}

int randV(Graph g){
    return numV(g) *(rand()/(RAND_MAX + 1.0));
}

Graph makeGraph(int V, int E){
    Graph g = newGraph(V);
    while(numE(g) < E){
        int v1 = randV(g);
        int v2 = randV(g);
        int w = randV(g);
        if(v1 != v2){
            insertE(g, mkEdge(v1, v2, w));
        }
    }
    return g;
}


int main(int argc, char * argv[]){
    srand(time(NULL));
    printf("Here is my random graph\n");
    show(randG);

    testNumV();
    //    testMkEdge();
    //    testNewGraph();
    //    testInsertE();
    //    testIsAdjacent();
    //    testAdjacentVertices();
    //    testIncidentEdges();
    //    testEdges();
    //    testNumE();

    return 0;
}

void testNumV() {
    int i;
    Graph g = NULL;

    printf("------------------------------");
    printf("\n>>>Test int numv(graph g)<<<\n");
    printf("------------------------------");
    for (i = 1; i < 10; i++){
        printf("\n## test %d: %d vertices graph\n", i, i);
        g = newGraph(i);
        assert(numv(g) == i);
        destroygraph(g);
    }
    // test 0 vertex graph

}

void testNumE() {
    int v1, v2, v, j;
    Graph g = NULL;

    printf("------------------------------");
    printf("\n>>>Test int numE(Graph g)<<<\n");
    printf("------------------------------");
    for (v = 1; v < 10; v++) {
        j = 0;
        printf("\n## Test %d: %d vertices graph\n", i, i);
        g = newGraph(i);
        v1 = 0;
        while (v1 < v) {
            v2 = v1 + 1;
            while(v2 < v) {
                insertE(g,mkEdge(v1, v2, 0));
                j++;
                assert(numE(g) == j);
                printf("\n ## passed ##\n");
                v2++;
            }
        }
        destroyGraph(g);
    }
}

void testMkEdge() {
    Graph g = NULL;

    printf("------------------------------------------------------");
    printf("\n>>>Test Edge mkEdge(Vertex, Vertex, int weight)<<<\n");
    printf("------------------------------------------------------");
    //?problem: what is the valid weight range?
    //

    //test invalid vertices

    //test isolated 1 vertex graph

    //test valid vertices (for graph with 2 - 3 vertices)
     for (v = 1; v < 10; v++) {
        j = 0;
        printf("\n## Test %d: %d vertices graph\n", i, i);
        g = newGraph(i);
        v1 = 0;
        while (v1 < v) {
            v2 = v1 + 1;
            while(v2 < v) {
                insertE(g,mkEdge(v1, v2, 0));
                j++;
                assert(numE(g) == j);
                printf("\n ## passed ##\n");
                v2++;
            }
        }
        destroyGraph(g);
    }


}

void testNewGraph() {
    int i;
    graph g = null;

    printf("------------------------------");
    printf("\n>>>Test Graph newgraph(int)<<<\n");
    printf("------------------------------");
    for (i = 1; i < 10; i++){
        printf("\n## test %d: %d vertices graph\n", i, i);
        g = newGraph(i);
        assert(numv(g) == i);
        destroygraph(g);
    }
    // test 0 vertex graph


}

void testInsertEandIsAdjacent() {
    Graph g = NULL;
    int adj;
    printf("------------------------------------------------------");
    printf("\n>>>Test void insertE(Graph g, Edge e)<<<\n");
    printf("------------------------------------------------------");
    //?problem: what is the valid weight range?
    // how to check the weight?

    //test invalid vertices

    //test isolated 1 vertex graph

    //test valid vertices (for graph with 2 - 3 vertices)
     for (v = 1; v < 10; v++) {
        j = 0;
        printf("\n## Test %d: %d vertices graph\n", i, i);
        g = newGraph(i);
        v1 = 0;
        while (v1 < v) {
            v2 = v1 + 1;
            while(v2 < v) {
                adj = isAdjacent(g, v1, v2);
                assert(adj == 0);
                insertE(g,mkEdge(v1, v2, j));
                j++;
                assert(numE(g) == j);
                printf("\n ## passed insertE##\n");
                adj = isAdjacent(g, v1, v2);
                assert(adj == 1);
                printf("\n ## passed isAdjacent##\n");
                v2++;
            }
        }
        destroyGraph(g);
    }
}

void testAdjacentVertices();
void testIncidentEdges();
void testEdges();


/*
   {
// copy empty graph
// printf("\n## Test %d: empty tree\n",++i);
// Graph cpy = GRAPHcopy(NULL);
// assert(cpy == NULL);
// printf("\n ## passed ##\n");

// copy isolated 1 vertex graph
printf("\n## Test %d: copy isolated 1 vertex graph\n",++i);
g = randomGraph(1, 0);
printf("Original Graph:\n");
GRAPHshow(g);
cpy = GRAPHcopy(g);
//check number of vertices
assert(GRAPHnumV(cpy) == GRAPHnumV(g));
//check number of edges
assert(GRAPHnumE(cpy) == GRAPHnumE(g));
printf("Copied Graph:\n");
GRAPHshow(cpy);
GRAPHdestroy(g);
GRAPHdestroy(cpy);
printf("\n ## passed ##\n");

// copy 2 vertices disconnected graph
printf("\n## Test %d: copy 2 vertices disconnected graph\n",++i);
g = randomGraph(2, 0);
printf("Original Graph:\n");
GRAPHshow(g);
cpy = GRAPHcopy(g);
assert(GRAPHnumV(cpy) == GRAPHnumV(g));
assert(GRAPHnumE(cpy) == GRAPHnumE(g));
printf("Copied Graph:\n");
GRAPHshow(cpy);
GRAPHdestroy(g);
GRAPHdestroy(cpy);
printf("\n ## passed ##\n");


// copy 2 vertices connected graph
printf("\n## Test %d:  copy 2 vertices connected graph\n",++i);
g = randomGraph(2, 1);
printf("Original Graph:\n");
GRAPHshow(g);
cpy = GRAPHcopy(g);
assert(GRAPHnumV(cpy) == GRAPHnumV(g));
assert(GRAPHnumE(cpy) == GRAPHnumE(g));
printf("Copied Graph:\n");
GRAPHshow(cpy);
GRAPHdestroy(cpy);
GRAPHdestroy(g);
printf("\n ## passed ##\n");


// copy a multi node 2subgaph graph
printf("\n## Test %d: copy a multi node 2subgaph graph\n",++i);
g = GRAPHinit(4);
GRAPHinsertE(g,EDGE(0,1));
GRAPHinsertE(g,EDGE(3,2));
printf("Original Graph:\n");
GRAPHshow(g);
cpy = GRAPHcopy(g);
assert(GRAPHnumV(cpy) == GRAPHnumV(g));
assert(GRAPHnumE(cpy) == GRAPHnumE(g));
printf("Copied Graph:\n");
GRAPHshow(cpy);
GRAPHdestroy(cpy);
GRAPHdestroy(g);
printf("\n ## passed ##\n");

// copy a multi node connected graph
printf("\n## Test %d: copy a connected graph with max edges\n",++i);
g = randomGraph(4, 6);
printf("Original Graph:\n");
GRAPHshow(g);
cpy = GRAPHcopy(g);
assert(GRAPHnumV(cpy) == GRAPHnumV(g));
assert(GRAPHnumE(cpy) == GRAPHnumE(g));
printf("Copied Graph:\n");
GRAPHshow(cpy);
GRAPHdestroy(cpy);
GRAPHdestroy(g);
printf("\n ## passed ##\n");

}

void testGraphDegree() {
    int i = 0;
    int d = 0;
    Graph g = NULL;

    printf("------------------------------------------------------");
    printf("\n>>>>> Test int GRAPHdegree(Graph g, Vertex v) <<<<<\n");
    printf("------------------------------------------------------");

    //    // test empty graph, this should stop program
    //    printf("\n## Test %d: empty graph\n",++i);
    //    Graph cpy = GRAPHcopy(g);
    //    assert(cpy == NULL);
    //    printf("\n ## passed ##\n");

    // test isolated 1 vertex graph, 0 degree
    printf("\n## Test %d: isolated 1 vertex graph, 0 degree\n",++i);
    g = randomGraph(1, 0);
    GRAPHshow(g);
    d = GRAPHdegree(g, 0);
    assert(d == 0);
    GRAPHdestroy(g);
    printf("\n ## passed ##\n");


    // test 2 vertices disconnected graph, 0 degree
    printf("\n## Test %d:2 vertices disconnected graph,0 degree\n",++i);
    g = randomGraph(2, 0);
    GRAPHshow(g);
    d = GRAPHdegree(g, 0);
    assert(d == 0);
    GRAPHdestroy(g);
    printf("\n ## passed ##\n");


    // test 2 vertices connected graph, 1 degree
    printf("\n## Test %d:2 vertices connected graph, 1 degree\n",++i);
    g = randomGraph(2, 1);
    GRAPHshow(g);
    d = GRAPHdegree(g, 0);
    assert(d == 1);
    GRAPHdestroy(g);
    printf("\n ## passed ##\n");


    // test a 4 vertices disconnected graph, 0 degree
    printf("\n##Test %d:4 vertices disconnected graph,0 degree\n",++i);
    g = GRAPHinit(4);
    GRAPHinsertE(g,EDGE(0,1));
    GRAPHinsertE(g,EDGE(0,2));
    GRAPHshow(g);
    d = GRAPHdegree(g, 3);
    assert(d == 0);
    GRAPHdestroy(g);
    printf("\n ## passed ##\n");

    // test a 4 vertices disconnected graph, 1 degree
    printf("\n##Test %d:4 vertices disconnected graph,1 degree\n",++i);
    g = GRAPHinit(4);
    GRAPHinsertE(g,EDGE(0,1));
    GRAPHinsertE(g,EDGE(3,2));
    GRAPHshow(g);
    d = GRAPHdegree(g, 3);
    assert(d == 1);
    GRAPHdestroy(g);
    printf("\n ## passed ##\n");


    // test a 4 vertices disconnected graph, 2 degree
    printf("\n##Test %d:4 vertices disconnected graph,2 degree\n",++i);
    g = GRAPHinit(4);
    GRAPHinsertE(g,EDGE(0,1));
    GRAPHinsertE(g,EDGE(0,2));
    GRAPHshow(g);
    d = GRAPHdegree(g, 0);
    assert(d == 2);
    GRAPHdestroy(g);
    printf("\n ## passed ##\n");


    // test a 4 vertices disconnected graph, 3 degree
    printf("\n##Test %d:4 vertices connected graph,3 degree\n",++i);
    g = GRAPHinit(4);
    GRAPHinsertE(g,EDGE(0,1));
    GRAPHinsertE(g,EDGE(0,2));
    GRAPHinsertE(g,EDGE(0,3));
    GRAPHshow(g);
    d = GRAPHdegree(g, 0);
    assert(d == 3);
    GRAPHdestroy(g);
    printf("\n ## passed ##\n");
}
*/
