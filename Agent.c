#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Agent.h"

#define NO_END -1
//This struct stores information about an individual agent(detective or thief)
//You might want to add to this struct to store more information
struct agentRep{
    Vertex startLocation;
    Vertex currentLocation;
    Vertex destination;
    int currentCycle;
    int maxCycles;
    int initialStamina; //max stamina
    int stamina;  //current stamina
    int strategy;
    int * visited;
    Graph map;
    char * name;
};


static void swap(Edge *a, Edge* b) ;
static int partitionByVisit(Edge moves[], int lo, int hi) ;
static int partitionByWeight(Edge moves[], int lo, int hi) ;
static void quicksort(Edge mvs[], int lo, int hi, char sortBy) ;
static void sortByVisit(Agent a, Edge moves[], int lo, int hi) ;
static void sortByWeight(Edge moves[], int lo, int hi) ;
//This creates one individual thief or detective
//You may need to add more to this
Agent initAgent(Vertex start, int maxCycles,int stamina,
        int strategy, Graph g, char * name){
    if(start >= numV(g)){
        printf("Error starting vertex %d not valid\n",start);
        abort();
    }
    Agent agent = malloc(sizeof(struct agentRep));

    agent->startLocation = start;
    agent->destination = NO_END;
    agent->currentLocation = start;
    agent->currentCycle = 0;
    agent->maxCycles = maxCycles;
    agent->initialStamina = stamina;
    agent->stamina = stamina;
    agent->strategy = strategy;
    agent->map = g;
    agent->name = strdup(name);
    agent->visited = calloc(sizeof(int), numV(g));
    if (strategy == C_L_VISITED)
        agent -> visited[start]++;
    return agent;
}

void setDestination(Agent a, int end) {
    a->destination = end;
}

// Takes an array with all the possible edges and puts the ones the agent
// has enough stamina for into the filteredMoves array
// returns the number of filteredMoves
int filterEdges(Agent a,int numEdges,Edge *possibleMoves,Edge * filteredMoves){
    int numFiltered = 0;
    int i;
    for(i=0;i<numEdges;i++){
        if(possibleMoves[i].weight <= a->stamina){
            filteredMoves[numFiltered++] = possibleMoves[i];
        }
    }
    return numFiltered;
}
static Edge * getValidMoves(Graph g, Agent a, int * nValidEdges) {
    Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
    Edge * legalMoves = malloc(numV(g) * sizeof(Edge));

    //Get all edges to adjacent vertices
    int nEdges = incidentEdges(g, a->currentLocation,possibleMoves);

    //Filter out edges that the agent does not have enough stamina for
    *nValidEdges = filterEdges(a, nEdges, possibleMoves, legalMoves);
    free(possibleMoves);
    return legalMoves;
}
// Get a legal move. This should be a move that the agent has enough
// stamina to make and is a valid edge from the graph.
// You need to implement all other strategies.
Edge getNextMove(Agent agent,Graph g){
    Edge nextMove;
    //Stationary strategy useful for debugging
    if(agent->strategy == STATIONARY){
        nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
    }else if(agent->strategy == RANDOM){
        Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));

        //Get all edges to adjacent vertices
        int numEdges = incidentEdges(g,agent->currentLocation,possibleMoves);

        //Filter out edges that the agent does not have enough stamina for
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);
        if(numFilteredEdges!= 0){
            //nextMove is randomly chosen from the filteredEdges
            nextMove = filteredMoves[rand()%numFilteredEdges];
            agent -> stamina -= nextMove.weight;
        } else {
            //the agent must stay in the same location
            nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
            agent -> stamina = agent -> initialStamina; //max stamina
        }
        free(filteredMoves);
        free(possibleMoves);
    }else if(agent->strategy == C_L_VISITED){
        int nValidEs = 0;
        Edge * legalMoves = getValidMoves(g, agent, &nValidEs);
        if(nValidEs!= 0){
            sortByVisit(agent, legalMoves, 0, nValidEs - 1);
            Vertex dest0 = legalMoves[0].w;
            int j = 1;
            int c = 0;
            int * visited = agent -> visited;
            while (j < nValidEs && visited[dest0] ==
                    visited[legalMoves[j++].w]) c++;
            sortByWeight(legalMoves, 0, c);
            nextMove = legalMoves[0];
            agent -> stamina -= nextMove.weight;
        } else {
            //the agent must stay in the same location
            Vertex currentGeo = agent->currentLocation;
            nextMove = mkEdge(currentGeo, currentGeo, 0);
            agent -> stamina = agent -> initialStamina; //max stamina
        }
        free(legalMoves);
        //    }else if(agent->strategy == DFS){

}else {
    printf("Agent strategy not implemented yet\n");
    abort();
}
return nextMove;
}

static void swap(Edge *a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

static int partitionByVisit(Edge moves[], int lo, int hi) {
    int i, j;
    i = lo - 1;
    j = hi;

    int pivot = moves[hi].v;

    // pivot element
    while (1) {
        // increment i until we approach the element that shouldnt be in pivot
        while (moves[++i].v < pivot);
        // get the element towards the hi
        while (pivot < moves[--j].v && j != lo);

        // if the lo hand counter is greater than the hi, we stop
        if (i >= j) {
            break;
        }

        // now we swap elements
        swap(&(moves[i]), &(moves[j]));
    }

    // place the pivot
    swap(&(moves[i]), &(moves[hi]));
    // return the pivot index
    return i;
}

static int partitionByWeight(Edge moves[], int lo, int hi) {
    int i, j;
    i = lo - 1;
    j = hi;

    int pivot = moves[hi].weight;

    // pivot element
    while (1) {
        // increment i until we approach the element that shouldnt be in pivot
        while (moves[++i].weight < pivot);
        // get the element towards the hi
        while (pivot < moves[--j].weight && j != lo);

        // if the lo hand counter is greater than the hi, we stop
        if (i >= j) {
            break;
        }

        // now we swap elements
        swap(&(moves[i]), &(moves[j]));
    }

    // place the pivot
    swap(&(moves[i]), &(moves[hi]));
    // return the pivot index
    return i;
}

static void quicksort(Edge mvs[], int lo, int hi, char sortBy) {
    int i;
    if (lo >= hi) return;
    swap(&mvs[hi - 1], &mvs[(lo + hi) / 2]);
    if (sortBy == 'w') {
        if (mvs[lo].weight > mvs[hi - 1].weight)
            swap(&mvs[lo], &mvs[hi - 1]);
        if (mvs[hi - 1].weight > mvs[hi].weight)
            swap(&mvs[hi - 1], &mvs[hi]);
        if (mvs[lo].weight > mvs[hi - 1].weight)
            swap(&mvs[lo], &mvs[hi - 1]);
        i = partitionByWeight(mvs, lo, hi - 1);
        quicksort(mvs, lo, i - 1, sortBy);
        quicksort(mvs, i + 1, hi, sortBy);
    } else if (sortBy == 'v') {
        if (mvs[lo].v > mvs[hi - 1].v)
            swap(&mvs[lo], &mvs[hi - 1]);
        if (mvs[hi - 1].v > mvs[hi].v)
            swap(&mvs[hi - 1], &mvs[hi]);
        if (mvs[lo].v > mvs[hi - 1].v)
            swap(&mvs[lo], &mvs[hi - 1]);

        i = partitionByVisit(mvs, lo, hi - 1);
        quicksort(mvs, lo, i - 1, sortBy);
        quicksort(mvs, i + 1, hi, sortBy);
    }

}

static void sortByVisit(Agent a, Edge moves[], int lo, int hi) {
    int i = 0;
    int size = hi - lo + 1;
    int v = moves[i].v;
    for (i = 0; i < size; i++)
        moves[i].v = a -> visited[moves[i].w];
    quicksort(moves, lo, hi, 'v');
    for (i = 0; i < size; i++)
        moves[i].v = moves[i].w;
    quicksort(moves, lo, hi, 'v');
    for (i = 0; i < size; i++)
        moves[i].v = v;
}

static void sortByWeight(Edge moves[], int lo, int hi) {
    quicksort(moves, lo, hi, 'w');
}



//Actually perform the move, by changing the agent's state
//This function needs to be updated to adjust the agent's stamina
void makeNextMove(Agent agent,Edge move){
    agent->currentCycle++;
    agent->currentLocation = move.w;
    if (agent -> strategy == C_L_VISITED && move.v != move.w)
        agent -> visited[move.w]++;
}

Vertex getDestination(Agent agent){
    return agent->destination;
}

Vertex getCurrentLocation(Agent agent){
    return agent->currentLocation;
}


char * getName(Agent agent){
    return agent->name;
}

//Needs to be updated to print out vertex name information
//and * for cities with informants
void printAgent(Agent agent){
    int city = agent->currentLocation;
    printf("%s %d %s (%d%s)",agent->name,agent->stamina, getCityName(city), city, isInformant(city));
    if (strcmp(agent -> name, "T") == 0) {
        int end = agent -> destination;
        printf(" %s(%d)", getCityName(end), end);
    }
    putchar('\n');
}

//You may need to update this to free any extra memory you use
void destroyAgent(Agent agent){
    //YOU MAY NEED TO MODIFY THIS
    free(agent->name);
    free(agent);
}

