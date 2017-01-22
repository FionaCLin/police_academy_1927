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

   testNumV();
   //    testMkEdge();
   //    testNewGraph();
   //    testInsertEandIsAdjacent() ;
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
      assert(numV(g) == i);
      destroyGraph(g);
   }
   // test 0 vertex graph

}

void testNumE() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;

   printf("------------------------------");
   printf("\n>>>Test int numE(Graph g)<<<\n");
   printf("------------------------------");
   for (v = 1; v < 10; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i, i);
      g = newGraph(i);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            insertE(g,mkEdge(v1, v2, j));
            j++;
            assert(numE(g) == j);
            printf("\n ## passed ##\n");
         }
      }
      destroyGraph(g);
   }
}

void testMkEdge() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;

   printf("------------------------------------------------------");
   printf("\n>>>Test Edge mkEdge(Vertex, Vertex, int weight)<<<\n");
   printf("------------------------------------------------------");
   //?problem: what is the valid weight range?

   //test invalid vertices

   //test isolated 1 vertex graph

   //test valid vertices (for graph with 2 - 3 vertices)
   for (v = 1; v < 10; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i++, i);
      g = newGraph(i);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            insertE(g,mkEdge(v1, v2, j));
            j++;
            assert(numE(g) == j);
            printf("\n ## passed ##\n");
         }
      }
      destroyGraph(g);
   }
}

void testNewGraph() {
   int i;
   Graph g = NULL;

   printf("------------------------------");
   printf("\n>>>Test Graph newgraph(int)<<<\n");
   printf("------------------------------");
   for (i = 1; i < 10; i++){
      printf("\n## test %d: %d vertices graph\n", i, i);
      g = newGraph(i);
      assert(numV(g) == i);
      destroyGraph(g);
   }
   // test 0 vertex graph


}

void testInsertE() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int adj;
   int nAdjV;
   Edge es[10];
   Vertex vs[10];
   printf("--------------------------------------------");
   printf("\n>>>Test void insertE(Graph g, Edge e)<<<\n");
   printf("--------------------------------------------");
   //?problem: what is the valid weight range?
   // how to check the weight?

   //test invalid vertices

   //test isolated 1 vertex graph

   //test valid vertices (for graph with 2 - 3 vertices)
   for (v = 1; v < 10; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i, i);
      g = newGraph(i);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            adj = isAdjacent(g, v1, v2);
            assert(adj == 0);
            insertE(g,mkEdge(v1, v2, j));
            j++;
            assert(numE(g) == j);
            adj = isAdjacent(g, v1, v2);
            assert(adj == 1);
            printf("\n ## passed insertE##\n");
         }
      }
      destroyGraph(g);
   }
}


void testIsAdjacent() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int adj;
   int nAdjV;
   Edge es[10];
   Vertex vs[10];
   printf("------------------------------------------------------\n");
   printf(">>Test int isAdjacent(Graph g, Vertex v1, Vertex v2)<<\n");
   printf("------------------------------------------------------\n");
   //?problem: what is the valid weight range?
   // how to check the weight?

   //test invalid vertices

   //test isolated 1 vertex graph

   //test valid vertices (for graph with 2 - 3 vertices)
   for (v = 1; v < 10; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i, i);
      g = newGraph(i);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            j++;
            adj = isAdjacent(g, v1, v2);
            assert(adj == 0);
            insertE(g,mkEdge(v1, v2, j));
            adj = isAdjacent(g, v1, v2);
            assert(adj == 1);
            printf("\n ## passed isAdjacent##\n");
         }
      }
      destroyGraph(g);
   }
}


void testAdjacentVertices() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int adj;
   int nAdjV;
   Edge es[10];
   Vertex vs[10];
   printf("--------------------------------------------------------------------");
   printf("\n>>>Test int adjacentVertices(Graph g,Vertex v, Vertex vs [])<<<\n");
   printf("--------------------------------------------------------------------");
   //?problem: what is the valid weight range?
   // how to check the weight?

   //test invalid vertices

   //test isolated 1 vertex graph

   //test valid vertices (for graph with 2 - 3 vertices)
   for (v = 1; v < 10; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i, i);
      g = newGraph(i);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            j++;
            adj = isAdjacent(g, v1, v2);
            assert(adj == 0);
            insertE(g,mkEdge(v1, v2, j));
            nAdjV = adjacentVertices(g,v1, vs);
            assert(nAdjV == (v2 - v1));
            printf("\n ## passed adjacentVertices##\n");
            v2++;
         }
      }
      destroyGraph(g);
   }
}


void testIncidentEdges() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int adj;
   int nAdjV;
   Edge es[10];
   Vertex vs[10];
   printf("--------------------------------------------");
   printf("\n>>>Test void insertE(Graph g, Edge e)<<<\n");
   printf("--------------------------------------------");
   //?problem: what is the valid weight range?
   // how to check the weight?

   //test invalid vertices

   //test isolated 1 vertex graph

   //test valid vertices (for graph with 2 - 3 vertices)
   for (v = 1; v < 10; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i, i);
      g = newGraph(i);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            j++;
            adj = isAdjacent(g, v1, v2);
            assert(adj == 0);
            insertE(g,mkEdge(v1, v2, j));
            nAdjE = incidentEdges(g,v1, es);
            assert(nAdjE == (v2 - v1));
            printf("\n ## passed adjacentVertices##\n");
         }
      }
      destroyGraph(g);
   }
}


void testEdges() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int adj;
   int nAdjV;
   Edge es[10];
   Vertex vs[10];
   printf("--------------------------------------------");
   printf("\n>>>Test void insertE(Graph g, Edge e)<<<\n");
   printf("--------------------------------------------");
   //?problem: what is the valid weight range?
   // how to check the weight?

   //test invalid vertices

   //test isolated 1 vertex graph

   //test valid vertices (for graph with 2 - 3 vertices)
   for (v = 1; v < 10; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i, i);
      g = newGraph(i);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            j++;
            adj = isAdjacent(g, v1, v2);
            assert(adj == 0);
            insertE(g,mkEdge(v1, v2, j));
            assert(numE(g) == j);
            printf("\n ## passed insertE##\n");
            adj = isAdjacent(g, v1, v2);
            assert(adj == 1);
            printf("\n ## passed isAdjacent##\n");
            nAdjV = adjacentVertices(g,v1, vs);
            assert(nAdjV == (v2 - v1));
            printf("\n ## passed adjacentVertices##\n");
            nAdjE = incidentEdges(g,v1, es);
            assert(nAdjE == (v2 - v1));
            printf("\n ## passed adjacentVertices##\n");
         }
      }
      destroyGraph(g);
   }
}

