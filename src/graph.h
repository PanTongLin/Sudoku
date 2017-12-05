#include "list.h"
#include <stdio.h>


//	Graph Data Type Defintions 
typedef struct 
{
    int V;
    LIST** adjacency;
}GRAPH;

/*	=============== createGraph ==============
	Allocates dynamic memory for a graph and 
    returns its address to caller
	   Pre    V is number of vertice
	   Post   adjacency list has allocated or error returned
	   Return struct pointer or null if overflow 
*/
GRAPH* createGraph(int V)
{
//	Local Definitions 
    int i;

	GRAPH* graph;

//	Statements 
	graph = (GRAPH*) malloc (sizeof (GRAPH));
	if (graph)
    {
        graph->V         = V;
        graph->adjacency = (LIST**) malloc(V * sizeof(LIST*));
        for (i = 0; i < V; i++)
        {
            graph->adjacency[i] = createList();
        }
    } // if 

	return graph;
}	// createGraph

/*	================== destroyGraph =================
	Deletes all data in graph and recycles memory
	   Pre    pGraph is a pointer to a valid graph.
	   Post   All structure deleted
	   Return null Graph pointer
*/
GRAPH* destroyGraph (GRAPH* pGraph) 
{
//	Local Definitions
    int i;


//	Statements 
	if (pGraph)
    {
        for (i = 0; i < pGraph->V; i++)
            destroyList (pGraph->adjacency[i]);
    } // if 
    free (pGraph);
	return NULL;
}	// destroyGraph 

/*	================== addEdge =================
	Add edge into graph.
	   Pre    pGraph is pointer to valid graph
	          u is one of the vertex between this edge
              v is another vertex between this edge
	   Post   edge added or error
*/
void addEdge (GRAPH* pGraph, int u, int v)
{
    addNode(pGraph->adjacency[u], v);
    addNode(pGraph->adjacency[v], u);
}	// addEdge 

/*	================== printAdjacency =================
	Print the adjacency list of graph.
	   Pre    pGraph is pointer to valid graph
	   Post   list all content in adjacency list one vertex
              by one vertex
*/
void printAdjacency (GRAPH* pGraph)
{
//	Local Definitions
    int i;
    NODE *it;


//	Statements     
    for (i = 0; i < pGraph->V; i++)
    {
        printf("vertex %d : ", i);
        it = pGraph->adjacency[i]->head;

        while(it != NULL)
        {
            printf("%d ", it->vertex);
            it = it->link;
        } //while

        printf("\n");
    } //for
}	// printAdjacency 