#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Agent.h"

#define NO_END -1
#define YET -1
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
    int dfsCurMove;
    int originStrategy;
    int * visit;
    int * st;
    int * paths;
    Graph map;
    char * name;
};

int filterEdges(Agent a, int numEdges, Edge *possibleMoves, Edge * filteredMoves) ;
static Edge * getValidMoves(Graph g, Agent a, int * nValidEdges) ;
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
    agent->dfsCurMove = 0;
    agent->name = strdup(name);
    agent->visit = calloc(sizeof(int), numV(g));
    agent->st = calloc(sizeof(int), numV(g));
    agent->paths = NULL;
    if (strategy == C_L_VISITED)
        agent->visit[start]++;
    //set the start vertex of the visit array as the end of the visit so
    //in the getNextMove, it will start new dfs since it mark as the end
    //of the visit;
    if (strategy == DFS) agent->visit[start] = numV(g);
    if (strcmp(name, "T") == 0 ) {
        setThief(g, start);
    } else {
        if (strcmp(hasInformant(g, start), "*") == 0) { Vertex target =
            getThief(g);
            setDestination(agent, target);
        }
    }
    return agent;
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
    if (a->strategy == DFS)
        a->dfsCurMove = 0;

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
    printf("%s %d %s (%d%s)", agent->name, agent->stamina,
            getCityName(agent->map, city), city,
            hasInformant(agent->map, city));
    if (end != NO_END)
        printf(" %s (%d%s)", getCityName(agent->map, end), end, hasInformant(agent->map, end));
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
        //check if it need reset the path
        //when detective finish 1 dfs or it is 0 hour
        if (agent -> dfsCurMove == 0 || agent->currentCycle == 0) {
            agent->visit[curGPS] = 0;
            agent->dfsCurMove = 0;
            free(agent->paths);
            agent->paths = dfSearch(g, agent->initialStamina, curGPS, agent->st,agent->visit);
        }
        int nextMv = agent->dfsCurMove + 1;
        Vertex nextCity = agent->paths[nextMv];
        //make the nextCity move to return
        nextMove = getEdge(g, curGPS, nextCity);
        //check if the nextCity move is affordable
        if (nextMove.weight <= agent->stamina) {
            //reduce stamina
            agent->stamina -= nextMove.weight;
            agent->dfsCurMove++;
        } else {
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
            free(agent->paths);
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
    free(agent->st);
    free(agent->paths);
    free(agent);
}

