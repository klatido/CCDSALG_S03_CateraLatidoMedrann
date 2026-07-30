#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include "graph.h"

/* Performs Breadth-First Search from the starting vertex. */
int breadthFirstSearch(Graph *graph, const char *startName);

/* Performs Depth-First Search from the starting vertex. */
int depthFirstSearch(Graph *graph, const char *startName);

/* Returns 1 if a path exists between two vertices, otherwise 0. */
int pathExists(Graph *graph, const char *startName, const char *endName);

#endif