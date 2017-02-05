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

#define No_edge -1
#define MAXV 5
#define MAXE 10

void testMkEdge();
void testNewGraphNumV();
void testInsertE();
void testIsAdjacent();
void testAdjacentVertices();
void testIncidentEdges();
void testEdges();
void testNumE();



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

   testMkEdge();
   testNewGraphNumV();
   testInsertE();
   testIsAdjacent() ;
   testNumE();
   testAdjacentVertices();
   testIncidentEdges();
   testEdges();

   return 0;
}

void testMkEdge() {
   int v1, v2, v, j, i = 0;
   Edge e;
   v = 10;
   j = 0;
   printf("--------------------------\n");
   printf(">>>>>  Test  mkEdge  <<<<<\n");
   printf("--------------------------\n");
   printf("### Test invalid cases ###\n");
   printf("## Test %d make Edge{%d, %d, %d}\n", ++i, -v, v, v);
   e = mkEdge(-v, v, v);
   assert(e.v == No_edge);
   assert(e.w == No_edge);
   assert(e.weight == No_edge);
   printf("\nExpected output:\n");
   printf("Vertices can't be nagtive.\n");
   printf(" ## passed mkEdge ##\n\n");

   printf("## Test %d make Edge{%d, %d, %d}\n", ++i, v, -v, v);
   e = mkEdge(v, -v, v);
   assert(e.v == No_edge);
   assert(e.w == No_edge);
   assert(e.weight == No_edge);
   printf("\nExpected output:\n");
   printf("Vertices can't be nagtive.\n");
   printf(" ## passed mkEdge ##\n\n");

   printf("## Test %d make Edge{%d, %d, %d}\n", ++i, v, v, -v);
   e = mkEdge(v, v, -v);
   assert(e.v == No_edge);
   assert(e.w == No_edge);
   assert(e.weight == No_edge);
   printf("\nExpected output:\n");
   printf("Weight can't be nagtive.\n");
   printf(" ## passed mkEdge ##\n\n");


   for (v1 = 0; v1 < v; v1++) {
      i = 0;
      for(v2 = v1; v2 < v; v2++) {
         i++;
         j++;
         printf("## %d vertices %d edges graph ##\n", v, j);
         printf("## Test %d make Edge{%d, %d, %d}\n", i, v1, v2, v1);
         e = mkEdge(v1, v2, v1);
         assert(e.v == v1);
         assert(e.w == v2);
         assert(e.weight == v1);
         printf(" ## passed mkEdge ##\n\n");
      }
   }
}

void testNewGraphNumV() {
   int i = 0;
   Graph g = NULL;

   printf("------------------------------\n");
   printf(">>>Test Graph newgraph(int)<<<\n");
   printf(">>> Test int numV(graph g) <<<\n");
   printf("------------------------------\n");

   printf("Test invalid cases\n");
   printf("\n## test %d:\nCreate %d vertices graph:\n", i + 1, i);
   g = newGraph(i);
   assert(g == NULL);
   printf("\nExpected output:\n");
   printf("Number of Vertices must be positive integer.\n");
   printf(" ## passed newGraph ##\n\n");

   printf("\n## test %d: numV for NULL graph paramenter:\n", i + 2);
   assert(numV(g) == -1);
   printf("\nExpected output:\n");
   printf("Invalid NULL Graph has no vertex.\n");
   printf(" ## passed numV ##\n\n");


   for (i = 1; i < 4; i++){
      printf("\n## test %d:\nCreate %d vertices graph:\n", i, i);
      g = newGraph(i);
      show(g);
      assert(numV(g) == i);
      destroyGraph(g);
      printf(" ## passed newGraph & numV ##\n\n");
   }
}

void testInsertE() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int adj;
   Edge e = {0,0,0};
   printf("--------------------------\n");
   printf(">>>>>  Test insertE  <<<<<\n");
   printf("--------------------------\n");
   for (v = 1; v < 4; v++) {
      j = 0;
      g = newGraph(v);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            i++;
            printf("\n## test %d: %d vertices graph\n", i, v);
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            adj = isAdjacent(g, v1, v2);
            assert(adj == 0);
            insertE(g,mkEdge(v1, v2, j));
            show(g);
            j++;
            assert(numE(g) == j);
            adj = isAdjacent(g, v1, v2);
            assert(adj == 1);
            printf("\n ## passed insertE##\n");
         }
      }

   }

   g = newGraph(v);

   printf("### Test invalid cases ###\n");
   printf("## Test %d insert Edge{%d, %d, %d} in invalid NULL Graph\n\n", ++i, e.v, e.w, e.weight);
   insertE(NULL, e);
   printf("\nExpected output:\n");
   printf("Invalid Graph.\n");
   printf(" ## passed inserE ##\n\n");

   printf("## Test %d insert Edge{%d, %d, %d}\n\n", ++i, -v, v, v);
   e = mkEdge(-v, v, v);
   assert(e.v == No_edge);
   assert(e.w == No_edge);
   assert(e.weight == No_edge);
   insertE(g,e);
   printf("\nExpected output:\n");
   printf("Vertices can't be nagtive.\n");
   printf("Invalid edge {%d, %d, %d}.\n", e.v, e.w, e.weight);
   printf(" ## passed inserE ##\n\n");


   printf("## Test %d insert Edge{%d, %d, %d}\n\n", ++i, v, -v, v);
   e = mkEdge(v, -v, v);
   assert(e.v == No_edge);
   assert(e.w == No_edge);
   assert(e.weight == No_edge);
   insertE(g,e);
   printf("\nExpected output:\n");
   printf("Vertices can't be nagtive.\n");
   printf("Invalid edge {%d, %d, %d}.\n", e.v, e.w, e.weight);
   printf(" ## passed inserE ##\n\n");

   printf("## Test %d insert Edge{%d, %d, %d}\n\n", ++i, v, v, -v);
   e = mkEdge(v, v, -v);
   assert(e.v == No_edge);
   assert(e.w == No_edge);
   assert(e.weight == No_edge);
   insertE(g,e);
   printf("\nExpected output:\n");
   printf("Weight can't be nagtive.\n");
   printf("Invalid edge {%d, %d, %d}.\n", e.v, e.w, e.weight);
   printf(" ## passed inserE ##\n\n");

   destroyGraph(g);
}

void testIsAdjacent() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int adj;
   printf("-----------------------\n");
   printf(">>> Test isAdjacent <<<\n");
   printf("-----------------------\n");

   for (v = 1; v < 10; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i, v);
      g = newGraph(v);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            i++;
            printf("\n## test %d: %d vertices graph\n", i, v);
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            j++;
            adj = isAdjacent(g, v1, v2);
            assert(adj == 0);
            insertE(g,mkEdge(v1, v2, j));
            show(g);
            adj = isAdjacent(g, v1, v2);
            assert(adj == 1);
            printf("\n ## passed isAdjacent##\n");
         }
      }

   }

   g = newGraph(v);
   printf("### Test invalid cases ###\n");
   printf("## Test %d: %d is adjacent to %d in invalid NULL Graph\n\n", ++i, v, v);
   adj = isAdjacent(NULL, v, v);
   assert(adj == 0);
   printf("\nExpected output:\n");
   printf("Invalid Graph.\n");
   printf("\n ## passed isAdjacent##\n");

   printf("## Test %d: %d is adjacent to %d\n\n", ++i, -v, v);
   adj = isAdjacent(g, -v, v);
   printf("\nExpected output:\n");
   printf("Invalid vertices %d => %d.\n", -v, v);
   printf("\n ## passed isAdjacent##\n");


   printf("## Test %d: %d is adjacent to %d\n\n", ++i, v, -v);
   adj = isAdjacent(g, v, -v);
   printf("\nExpected output:\n");
   printf("Invalid vertices %d => %d.\n", v, -v);
   printf("\n ## passed isAdjacent##\n");

   destroyGraph(g);
}


void testNumE() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;

   printf("------------------------------");
   printf("\n>>>Test int numE(Graph g)<<<\n");
   printf("------------------------------\n");

   //test invalid
   printf("### Test invalid cases ###\n");
   printf("## Test invalid NULL graph\n\n");
   assert(numE(g) == No_edge);
   printf("\nExpected output:\n");
   printf("Invalid NULL Graph has no edges.\n");
   printf(" ## passed numE ##\n\n");

   for (v = 1; v < 10; v++) {
      j = 0;
      g = newGraph(v);
      for (v1 = 0; v1 < v; v1++) {
         i = 0;
         for(v2 = v1 + 1; v2 < v; v2++) {
            i++;
            j++;
            printf("##Test %d: %d vertices %d edges graph\n", i, v, j);
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, j);
            insertE(g,mkEdge(v1, v2, i));
            show(g);
            assert(numE(g) == j);
            printf(" ## passed numE ##\n\n");
         }
      }
   }
}



void testAdjacentVertices() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int adj;
   int nAdjV;
   int nAdjE;
   Vertex vs[10];
   Edge es[10];
   printf("---------------------------\n");
   printf(">>>Test adjacentVertices<<<\n");
   printf("---------------------------\n");

   for (v = 1; v < 4; v++) {
      j = 0;
      printf("\n## Test %d: %d vertices graph\n", i, v);
      g = newGraph(v);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            i++;
            printf("\n## test %d: %d vertices graph\n", i, v);
            printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, v1);
            j++;
            adj = isAdjacent(g, v1, v2);
            assert(adj == 0);
            insertE(g,mkEdge(v1, v2, v1));
            nAdjV = adjacentVertices(g,v1, vs);
            nAdjE = incidentEdges(g, v1, es);
            assert(nAdjE == nAdjV);
            for (j = 0; j < nAdjV; j++) {
               assert(isAdjacent(g, v1, vs[j]) == 1);
            }
            printf("All vertices returned are adjacent to %d.\n", v1);
            printf("\n ## passed adjacentVertices##\n");
         }
      }
      destroyGraph(g);
   }

   g = newGraph(v);
   printf("### Test invalid cases ###\n");
   printf("## Test %d: %d adjacent vertices in invalid NULL Graph\n\n", ++i, v);
   nAdjV = adjacentVertices(NULL, v, vs);
   assert(nAdjV == 0);
   printf("\nExpected output:\n");
   printf("Invalid Graph.\n");
   printf(" ## passed adjacentVertices##\n");

   printf("\n## Test %d: %d adjacent Vertice\n\n", ++i, -v);
   nAdjV = adjacentVertices(g, -v, vs);
   assert(nAdjV == 0);
   printf("\nExpected output:\n");
   printf("Invalid vertex %d.\n", -v);
   printf(" ## passed adjacentVertices##\n");

   destroyGraph(g);

}


void testIncidentEdges() {
   int v1, v2, v, j, i = 1;
   Graph g = NULL;
   int adj;
   int nAdjE;
   int nAdjV;
   Edge es[10];
   Vertex vs[10];
   printf("--------------------------\n");
   printf(">>> Test incidentEdges <<<\n");
   printf("--------------------------\n");
   v = 10;
   printf("\n## Test %d: %d vertices graph\n", i, v);
   if (i == 1)
      printf("\nNo edge can show\n");
   i++;
   g = newGraph(v);
   for (v1 = 0; v1 < v; v1++) {
      j = 0;
      for(v2 = v1 + 1; v2 < v; v2++) {
         printf("\n## test %d edges graph\n", numE(g) + 1);
         printf("\n##insert Edge{%d, %d, %d}\n", v1, v2, v1 );
         adj = isAdjacent(g, v1, v2);
         assert(adj == 0);
         insertE(g,mkEdge(v1, v2, v1));
         show(g);
         nAdjE = incidentEdges(g, v1, es);
         nAdjV = adjacentVertices(g,v1, vs);
         assert(nAdjE == nAdjV);
         for (j = 0; nAdjE != 0 && j < nAdjE; j++) {
               int adj = isAdjacent(g, es[j].v, es[j].w);
               assert(adj == 1);
         }
         printf("All edges returned are in the graph.\n");
         printf("\n ## passed incidentEdges##\n");
      }
   }
   destroyGraph(g);

   g = newGraph(v);
   printf("### Test invalid cases ###\n");
   printf("## Test %d: %d incident edges in invalid NULL Graph\n\n", ++i, v);
   nAdjE = incidentEdges(NULL,v, es);
   assert(nAdjE == 0);
   printf("\nExpected output:\n");
   printf("Invalid Graph.\n");
   printf(" ## passed incidentEdges##\n");

   printf("\n## Test %d: %d adjacent Vertice\n\n", ++i, -v);
   nAdjE = incidentEdges(g, -v, es);
   assert(nAdjE == 0);
   printf("\nExpected output:\n");
   printf("Invalid vertex %d.\n", -v);
   printf(" ## passed incidentEdges##\n");


}


void testEdges() {
   int v1, v2, v, j, i = 0;
   Graph g = NULL;
   int ne;
   printf("--------------------------------------------");
   printf("\n>>>Test edges funtion<<<\n");
   printf("--------------------------------------------");


   for (v = 1; v < 10; v++) {
      printf("\n## Test %d vertices graph\n", v);
      g = newGraph(v);
      for (v1 = 0; v1 < v; v1++) {
         for(v2 = v1 + 1; v2 < v; v2++) {
            i++;
            j = numE(g) + 1;
            printf("-------------------------------\n");
            printf("^^^ Test %d: %d edges graph ^^^\n", i, j+1);
            printf("-------------------------------\n");
            printf("## Insert Edge{%d, %d, %d} ##\n", v1, v2, j);
            insertE(g, mkEdge(v1, v2, j));
            Edge e[j];
            ne = edges(e, j, g);
            for (j = 0; ne != 0 && j < numE(g); j++) {
               int adj = isAdjacent(g, e[j].v, e[j].w);
               assert(adj == 1);
            }
            printf("All edges returned are in the graph.\n");
            assert(ne == j);
            printf("## passed edges function ##\n");
         }
      }

   }

   printf("\n### Test invalid cases ###\n");
   printf("## Test invalid NULL graph\n\n");
   Edge e[j];
   ne = edges(e, j, NULL);
   assert(ne == 0);
   printf("\nExpected output:\n");
   printf("Invalid Graph.\n");
   printf(" ## passed numE ##\n\n");



}

