#ifndef STDIO_H
    #define STDIO_H
#endif
#include "graph.h"


int main()
{
    GRAPH *graph = createGraph(5); //5 is the # of vertice
    addEdge(graph, 0, 1);
    addEdge(graph, 2, 4);
    addEdge(graph, 1, 3);

    printAdjacency(graph);

    destroyGraph(graph);

    return 0;
}