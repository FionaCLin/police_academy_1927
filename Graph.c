/*
   Graph.c


*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"


struct graphRep {
   int nv;
   int ne;
   int ** edges;
};

static int validV(Graph g, Vertex v) {
   return (v >= 0 && v < g->nV);
}
// Create an edge from v to w
Edge mkEdge(Vertex v, Vertex w, int weight) {
   assert(v >= 0 && w >= 0);
   Edge e = {v,w,weight};
   return e;
}

//Initialise a new graph
Graph newGraph(int nV) {
   if (nV < 0) {
      printf("Number of Vertices must be positive integer.\n");
      return NULL;
   }
   int i, j;
   Graph g = malloc(sizeof(struct GraphRep));
   if (g == NULL) {
      printf("Unable to create Graph.\n");
      return NULL;
   }
   g->edges = calloc(sizeof(int *), nV);
   if (g->edges != NULL) {
      printf("Unable to make Graph edges.\n");
      return NULL;
   }
   for (i = 0; i < nV; i++)
      g->edges[i] = calloc(sizeof(int), i);
   g->nv = nV;
   g->ne = 0;
   return g;
}

//Insert an edge into a graph
//the edge must not be inserted if
//     the vertices are not valid
//     it would create a self loop
//     there already exists an edge between the vertices
void insertE(Graph g, Edge e) {
   assert(g != NULL);

   //COMPLETE THIS
}

//returns 1 if there is an edge from v to w
//returns 0 otherwise
int isAdjacent(Graph g, Vertex v, Vertex w){
   //COMPLETE THIS
   return 0;
}

//returns the number of adjacent vertices
//and fills the adj array with the adjacent vertices
int adjacentVertices(Graph g, Vertex v, Vertex adj[]){
   //COMPLETE THIS
   return 0;
}

//returns the number of incident edges
//and fills the edges with incident edges
int incidentEdges(Graph g, Vertex v, Edge edges[]){
   //COMPLETE THIS
   return 0;
}

void destroyGraph(Graph g){
   if (g != NULL){
      int i;
      if(g -> edges != NULL) {
         for (i = 0; i < g -> nv; i++)
            free(g -> edges[i]);
      }
      free(g -> edges);
   }
   free(g);
}

//return the number of vertices in the graph
int numV(Graph g){
   if (g == NULL) {
      printf("Invalid NULL Graph has no vertex.\n");
      return -1;
   }
   return g -> nv;
}

//return the number of edges in the graph
int numE(Graph g){
   if (g == NULL) {
      printf("Invalid NULL Graph has no edges.\n");
      return -1;
   }
   return g -> ne;
}

// returns the number of edges and fills the array of edges.
// nE is the max size of the es array
// The edges in the edges function should be in ascending order and not
// contain duplicates.
int edges(Edge es[], int nE, Graph g){
   //COMPLETE THIS
   return -1;
}

//Display the graph
void show(Graph g) {
   assert(g != NULL);
   printf("V=%d, E=%d\n", numV(g), numE(g));
   int i, j;
   for (i = 0; i < numV(g); i++) {
      int nshown = 0;
      for (j = 0; j < numV(g); j++) {
         if (isAdjacent(g,i,j)) {
            printf("%d-%d : TODO ",i,j);
            nshown++;
         }
      }
      if (nshown > 0){
         printf("\n");
      }
   }
}
