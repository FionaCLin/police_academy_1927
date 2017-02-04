#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Agent.h"

#define NO_END -1
//This struct stores information about an individual agent(detective or
//thief) You might want to add to this struct to store more information
struct agentRep{
    Vertex startLocation;
    Vertex currentLocation;
    Vertex destination;
    int currentCycle;
    int maxCycles;
    int initialStamina; //max stamina
    int stamina; //current stamina
    int strategy;
    int originStrategy;
    int * visit;
    int * paths;
    Graph map;
    char * name;
};


// static void swap(Edge *a, Edge* b) ; static int
// partitionByWeight(Edge moves[], int lo, int hi) ; static void
// quicksort(Edge mvs[], int lo, int hi, char sortBy) ; static void
// sortByWeight(Edge moves[], int lo, int hi) ;
static Edge sortByVisit(Agent a, Edge moves[], int lo, int hi) ;
//This creates one individual thief or detective You may need to add
//more to this
Agent initAgent(Vertex start, int maxCycles, int stamina, int strategy,
        Graph g, char * name) {
    if (start >= numV(g)) {
        printf("Error starting vertex %d not valid\n", start);
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
    agent->originStrategy = strategy;
    agent->map = g;
    agent->name =
        strdup(name);
    agent->visit = calloc(sizeof(int), numV(g));
    //agent->paths = calloc(sizeof(int), numV(g));
    agent->paths = NULL;
    if (strategy == C_L_VISITED)
        agent->visit[start]++;
    //set the start vertex of the visit array as the end of the visit so
    //in the getNextMove, it will start new dfs since it mark as the end
    //of the visit;
    if (strategy == DFS) agent->visit[start] = numV(g);
    if (strcmp(name, "T") == 0 ) {
        setThief(start);
    } else {
        if (strcmp(hasInformant(start), "*") == 0) { Vertex target =
            getThief();
            setDestination(agent, target);
        } } return agent;
}

void setDestination(Agent a, int end) {
    //when detective meet informant, this will be called to set the
    //destination for the detective therefore we update their strategy
    //by the way.
    if (strcmp(a->name, "T") != 0)
        setStrategy(a, L_T_P);
    a->destination = end;
}

void setStrategy(Agent a, int newStrategy) {
    a->strategy = newStrategy;
    //when detective finish L_T_P, this will be called to re-assigned the
    //original strategy and remove the destination
    if (strcmp(a->name, "T") != 0) {
        //update no destionation
        a->destination = NO_END;
        //set no path
        free(a->paths);
        a->paths = NULL;

    }
}

Vertex getDestination(Agent agent) {
    return agent->destination;
}

Vertex getCurrentLocation(Agent agent) {
    return agent->currentLocation;
}

char * getName(Agent agent) {
    return agent->name;
}

//Needs to be updated to print out vertex name information
//and * for cities with informants
void printAgent(Agent agent) {
    int city = agent->currentLocation;
    int end = agent->destination;
    printf("%s %d %s (%d%s)", agent->name, agent->stamina, getCityName(city), city, hasInformant(city));
    if (end != NO_END)
        printf(" %s (%d)", getCityName(end), end);
    putchar('\n');
}

static Edge sortByVisit(Agent a, Edge mvs[], int lo, int hi) {
    int size = hi - lo + 1;
    if (size == 1) return mvs[lo];
    int i;
    int least = lo;
    for (i = lo + 1; i <= hi; i++) {
        if (a->visit[mvs[least].w] > a->visit[mvs[i].w]) {
            least = i;
        } else if (a->visit[mvs[least].w] == a->visit[mvs[i].w]) {
            if (mvs[least].weight > mvs[i].weight) {
                least = i;
            } else if (mvs[least].weight == mvs[i].weight) {
                if (mvs[least].w > mvs[i].w) {
                    least = i;
                }
            }
        }
    }
    return mvs[least];
}


// Takes an array with all the possible edges and puts the ones the agent
// has enough stamina for into the filteredMoves array
// returns the number of filteredMoves
int filterEdges(Agent a, int numEdges, Edge *possibleMoves, Edge * filteredMoves) {
    int numFiltered = 0;
    int i;
    for (i=0;i<numEdges;i++) {
        if (possibleMoves[i].weight <= a->stamina) {
            filteredMoves[numFiltered++] = possibleMoves[i];
        }
    }
    return numFiltered;
}

static Edge * getValidMoves(Graph g, Agent a, int * nValidEdges) {
    Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
    Edge * legalMoves = malloc(numV(g) * sizeof(Edge));

    //Get all edges to adjacent vertices
    int nEdges = incidentEdges(g, a->currentLocation, possibleMoves);

    //Filter out edges that the agent does not have enough stamina for
    *nValidEdges = filterEdges(a, nEdges, possibleMoves, legalMoves);
    free(possibleMoves);
    return legalMoves;
}
// Get a legal move. This should be a move that the agent has enough
// stamina to make and is a valid edge from the graph.
// You need to implement all other strategies.
Edge getNextMove(Agent agent, Graph g) {
    Edge nextMove;
    //Stationary strategy useful for debugging
    if (agent->strategy == STATIONARY) {
        nextMove = mkEdge(agent->currentLocation, agent->currentLocation, 0);
    } else if (agent->strategy == RANDOM) {
        Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));

        //Get all edges to adjacent vertices
        int numEdges = incidentEdges(g, agent->currentLocation, possibleMoves);

        //Filter out edges that the agent does not have enough stamina for
        int numFilteredEdges = filterEdges(agent, numEdges, possibleMoves, filteredMoves);
        if (numFilteredEdges!= 0) {
            //nextMove is randomly chosen from the filteredEdges
            nextMove = filteredMoves[rand()%numFilteredEdges];
            agent->stamina -= nextMove.weight;
        } else {
            //the agent must stay in the same location
            nextMove = mkEdge(agent->currentLocation, agent->currentLocation, 0);
            agent->stamina = agent->initialStamina;
            //max stamina
        }
        free(filteredMoves);
        free(possibleMoves);
    } else if (agent->strategy == C_L_VISITED) {
        int nValidEs = 0;
        Edge * legalMoves = getValidMoves(g, agent, &nValidEs);
        if (nValidEs!= 0) {
            nextMove = sortByVisit(agent, legalMoves, 0, nValidEs - 1);
            agent->stamina -= nextMove.weight;
        } else {
            //the agent must stay in the same location
            Vertex currentGeo = agent->currentLocation;
            nextMove = mkEdge(currentGeo, currentGeo, 0);
            agent->stamina = agent->initialStamina;
            //max stamina
        }
        free(legalMoves);
    } else if (agent->strategy == DFS) {
        int curGPS = agent->currentLocation;
        int order = agent->visit[curGPS];
        if (agent->paths == NULL) {
            order = numV(g);
        }
        //if the order of the agent's current location equal to the
        //number of Cities in the grap/map means the agent arrived the
        //end of DFS thus it need to reset to 0 and free the old path
        //then get the new DFS path
        if (order == numV(g)) {
            agent->visit[curGPS] = 0;
            free(agent->paths);
            agent->paths = dfSearch(g, curGPS, agent->visit);
        }
        // update the order of current location in order to get the next
        // city to visit
        order = agent->visit[curGPS];
        Vertex nextCity = agent->paths[order];
        // check if there is path to nextCity city
        if (!isAdjacent(g, curGPS, nextCity)) {
            // if not, then move backward and update the nextCity city to visit
            agent->paths[order] = agent->paths[order - 1];
            agent->paths[order - 1] = nextCity;
            nextCity = agent->paths[order - 2];
        }
        //get the nextCity move
        nextMove = getEdge(g, curGPS, nextCity);
        //check if the nextCity move is affordable
        if (nextMove.weight <= agent->stamina)
            //reduce stamina
            agent->stamina -= nextMove.weight;
        else {
            //the agent must stay in the same location
            nextMove = mkEdge(curGPS, curGPS, 0);
            //max stamina
            agent->stamina = agent->initialStamina;
        }
    } else if (agent->strategy == L_T_P) {
        //get current location and the destination
        int curGPS = agent->currentLocation;
        int dest = agent->destination;
        //check if detective hasn't his less turn path
        if (agent->paths == NULL) {
            // get the max stamina to the detective has the stamina reset
            // the stamina after rest.
            int max = agent->stamina;
            // get current stamina to compute the end stamina along the paths
            int cur = agent->stamina;
            //work out the less turn path
            agent->paths = bfSearch(g, max, cur, curGPS, dest);
        }
        //first element of the paths record my current spot in the paths
        // increment 1 to get the next spot in the paths
        int order = agent->paths[0] + 1;
        Vertex nextCity = agent->paths[order];
        //get the nextCity move
        nextMove = getEdge(g, curGPS, nextCity);
        //check if the nextCity move is affordable
        if (nextMove.weight <= agent->stamina) {
            //reduce stamina
            agent->stamina -= nextMove.weight;
            // update the first element
            agent->paths[0]++;
        } else {
            //the agent must stay in the same location
            nextMove = mkEdge(curGPS, curGPS, 0);
            //max stamina
            agent->stamina = agent->initialStamina;
        }

    } else {
        printf("Agent strategy not implemented yet\n");
        abort();
    }
    return nextMove;
}

//Actually perform the move, by changing the agent's state
//This function needs to be updated to adjust the agent's stamina
void makeNextMove(Agent agent, Edge move) {
    agent->currentCycle++;
    agent->currentLocation = move.w;
    if (agent->strategy == C_L_VISITED)
        //??stay the same city count as 2 visits??
        agent->visit[move.w]++;
    if (agent->strategy == L_T_P) {
        // update the visit array if the agent original strategy is
        // C_L_VISITED
        if (agent->originStrategy == C_L_VISITED)
            agent->visit[move.w]++;
        if (agent->currentLocation == agent->destination)
            setStrategy(agent, agent->originStrategy);
    }
}

//You may need to update this to free any extra memory you use
void destroyAgent(Agent agent) {
    //YOU MAY NEED TO MODIFY THIS
    free(agent->name);
    free(agent->visit);
    free(agent->paths);
    free(agent);
}

// static void swap(Edge *a, Edge* b) {
//     Edge temp = *a;
//     *a = *b;
//     *b = temp;
// }

// static int partitionByVisit(Edge moves[], int lo, int hi) {
//     int i, j;
//     i = lo - 1;
//     j = hi;

//     int pivot = moves[hi].v;

//     // pivot element
//     while (1) {
//         // increment i until we approach the element that shouldnt be in pivot
//         while (moves[++i].v < pivot);
//         // get the element towards the hi
//         while (pivot < moves[--j].v && j != lo);

//         // if the lo hand counter is greater than the hi, we stop
//         if (i >= j) {
//             break;
//         }

//         // now we swap elements
//         swap(&(moves[i]), &(moves[j]));
//     }

//     // place the pivot
//     swap(&(moves[i]), &(moves[hi]));
//     // return the pivot index
//     return i;
// }

// static int partitionByWeight(Edge moves[], int lo, int hi) {
//     int i, j;
//     i = lo - 1;
//     j = hi;

//     int pivot = moves[hi].weight;

//     // pivot element
//     while (1) {
//         // increment i until we approach the element that shouldnt be in pivot
//         while (moves[++i].weight < pivot);
//         // get the element towards the hi
//         while (pivot < moves[--j].weight && j != lo);

//         // if the lo hand counter is greater than the hi, we stop
//         if (i >= j) {
//             break;
//         }

//         // now we swap elements
//         swap(&(moves[i]), &(moves[j]));
//     }

//     // place the pivot
//     swap(&(moves[i]), &(moves[hi]));
//     // return the pivot index
//     return i;
// }

// static void quicksort(Edge mvs[], int lo, int hi, char sortBy) {
//     int i;
//     if (lo >= hi) return;
//     swap(&mvs[hi - 1], &mvs[(lo + hi) / 2]);
//     if (sortBy == 'w') {
//         if (mvs[lo].weight > mvs[hi - 1].weight)
//             swap(&mvs[lo], &mvs[hi - 1]);
//         if (mvs[hi - 1].weight > mvs[hi].weight)
//             swap(&mvs[hi - 1], &mvs[hi]);
//         if (mvs[lo].weight > mvs[hi - 1].weight)
//             swap(&mvs[lo], &mvs[hi - 1]);
//         i = partitionByWeight(mvs, lo, hi - 1);
//         quicksort(mvs, lo, i - 1, sortBy);
//         quicksort(mvs, i + 1, hi, sortBy);
//     } else if (sortBy == 'v') {
//         if (mvs[lo].v > mvs[hi - 1].v)
//             swap(&mvs[lo], &mvs[hi - 1]);
//         if (mvs[hi - 1].v > mvs[hi].v)
//             swap(&mvs[hi - 1], &mvs[hi]);
//         if (mvs[lo].v > mvs[hi - 1].v)
//             swap(&mvs[lo], &mvs[hi - 1]);

//         i = partitionByVisit(mvs, lo, hi - 1);
//         quicksort(mvs, lo, i - 1, sortBy);
//         quicksort(mvs, i + 1, hi, sortBy);
//     }

// }

// static void sortByWeight(Edge moves[], int lo, int hi) {
//     quicksort(moves, lo, hi, 'w');
// }

