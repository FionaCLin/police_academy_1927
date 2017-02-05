// An graph ADT interface for weighted undirected graphs

#include <limits.h>
#include "Path.h"

#ifndef GRAPH_H
#define GRAPH_H

#define NOT_YET (-1)
#define NO_EDGE (-1)

// vertices denoted by integers 0..N-1
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct {
    Vertex v;
    Vertex w;
    int weight;
} Edge;

Edge mkEdge(Vertex, Vertex, int);

// graph representation is hidden
typedef struct graphRep *Graph;

// check if the city has informant
char * hasInformant(int city);

//set thief location
void setThief(Vertex city) ;
//get thief location
Vertex getThief() ;

// Create an edge from v to w
// read std io for each city info
void readCityInfo(int city, char info,char * name);

// fetch city's name
char * getCityName(int city);

// operations on graphs
Graph newGraph(int nV); // #vertices

// insert an edge into the graph
// the edge must not be inserted if
//     the vertices are not valid
//     it would create a self loop
//     there already exists an edge between the vertices
void insertE(Graph g, Edge e);

//returns 1 if there is ad adge from v to w
int isAdjacent(Graph g,Vertex v, Vertex w);

//returns the number of adjacent vertices
//and fills the adj array with the adjacent vertices
int adjacentVertices(Graph g, Vertex v, Vertex adj[]);

//returns the number of incident edges
//and fills the edges with incident edges
int incidentEdges(Graph g, Vertex v, Edge edges[]);

// returns the number of edges and fills the array of edges.
// nE is the max size of the es array
int edges(Edge es[], int nE, Graph g);

int numV(Graph g);
int numE(Graph g);

//YOU DO NOT NEED ASSERT BASED TESTS FOR THESE FUNCTIONS
void destroyGraph(Graph g);
void show(Graph g);


//YOU MAY ADD MORE FUNCTIONS IN HERE FOR YOUR OWN IMPLEMENTATION
//DO NOT SUBMIT UNIT TESTS FOR THESE FUNCTIONS - OF COURSE
//YOU SHOULD TEST THEM ANYWAY BUT COMMENT OUT OR REMOVE TESTS FOR
//SUBMISSION OTHERWISE

// dfSearch using Stack
//The initialisation of variables etc before we call the dfs function
int * dfSearch(Graph g, int maxStamina, Vertex src, int * st, int * visit) ;
Edge getEdge(Graph g, Vertex v, Vertex w);
int * bfSearch(Graph g, int maxStamina, int curStamina, Vertex src, Vertex dest) ;
#endif
