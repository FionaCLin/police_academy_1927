/*
   Graph.c


*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "Graph.h"

#define NO_EDGE FLT_MAX

struct graphRep {
   int nv;
   int ne;
   float ** edges;
};

static int validE(Graph g, Edge e) {
   return (e.v >= 0 && e.v < g -> nv && e.w >= 0 && e.w < g -> nv);
}
static int validV(Graph g, Vertex v) {
   return (v >= 0 && v < g -> nv);
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
   Graph g = malloc(sizeof(struct graphRep));
   if (g == NULL) {
      printf("Unable to create Graph.\n");
      return NULL;
   }
   g -> edges = calloc(sizeof(float*), nV);
   if (g -> edges != NULL) {
      printf("Unable to make Graph edges.\n");
      return NULL;
   }
   for (i = 0; i < nV; i++) {
      g -> edges[i] = malloc(sizeof(float)* (i + 1));
      for(j = 0; j < i + 1; j++)
         g -> edges[i][j] = NO_EDGE;
   }
   g -> nv = nV;
   g -> ne = 0;
   return g;
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
      return ;
   }
   if (!validE(g, e)) {
      printf("Invalid edge.\n");
      return ;
   }
   row = e.v;
   col = e.w;
   if (e.v < e.w) {
      row = e.w;
      col = e.v;
   }
   if (g -> edges[row][col] == NO_EDGE) {
      g -> edges[row][col] = e.weight;
      g -> ne++;
   }
}

//returns 1 if there is an edge from v to w
//returns 0 otherwise
int isAdjacent(Graph g, Vertex v, Vertex w){
   int col, row;
   if (g == NULL) {
      printf("Invalid Graph.\n");
      return 0;
   }
   Edge e = {v, w};
   if (!validE(g, e)) {
      printf("Invalid vertices %d - %d.\n", v, w);
      return 0;
   }
   row = e.v;
   col = e.w;
   if (e.v < e.w) {
      row = e.w;
      col = e.v;
   }
   if (g -> edges[row][col] == NO_EDGE)
      return 0;
   return 1;
}

//returns the number of adjacent vertices
//and fills the adj array with the adjacent vertices
int adjacentVertices(Graph g, Vertex v, Vertex adj[]){
   int i, nv = 0;
   if (!validV(g, v)) {
      printf("Invalid Vertex\n");
      return 0;
   }
   adj = malloc(sizeof(int *));
   if (adj == NULL) {
      printf("System runs out memory\n");
      return -1;
   }
   for (i = 0; i < v; i++)
      if (g -> edges[v][i] != NO_EDGE) {
         adj = realloc(adj, sizeof(int *) * nv + 1);
         adj[nv++]= i;
      }
   for (i = v + 1; i < g -> nv; i++)
      if (g -> edges[i][v] != NO_EDGE) {
         adj = realloc(adj, sizeof(int *) * nv + 1);
         adj[nv++]= i;
      }
   return nv;
}

//returns the number of incident edges
//and fills the edges with incident edges
int incidentEdges(Graph g, Vertex v, Edge edges[]){
   int i, ne = 0;
   if (!validV(g, v)) {
      printf("Invalid Vertex\n");
      return 0;
   }
   edges = malloc(sizeof(struct Edge));
   if (adj == NULL) {
      printf("System runs out memory\n");
      return -1;
   }
   for (i = 0; i < v; i++)
      if (g -> edges[v][i] != NO_EDGE) {
         edges = realloc(edges, sizeof(struct Edge) * ne + 1);
         edges[ne++] = mkEdge(v, i, g -> edges[v][i]);
      }
   for (i = v + 1; i < g -> nv; i++)
      if (g -> edges[i][v] != NO_EDGE) {
         edges = realloc(edges, sizeof(struct Edge) * ne + 1);
         edges[ne++] = mkEdge(v, i, g -> edges[i][v]);
      }
   return ne;
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
   int v, w, count = 0;
   for (v = 0; v < g -> nv; v++)
      for(w = 0; w < v; w++)
         if (g -> edges[v][w] && count < nE)
            es[count++] = mkEdge(v, w, g -> edges[v][w]);
   return count;
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
