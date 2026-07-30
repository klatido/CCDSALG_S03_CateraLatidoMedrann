#ifndef MST_H
#define MST_H

#include "graph.h"

/*
 * Creates the Minimum Spanning Tree of the given graph
 * using Prim's Algorithm.
 *
 * The resulting MST is stored in mstGraph.
 *
 * Returns:
 * 1 if the MST was created successfully
 * 0 if the graph is empty, disconnected,
 *   or memory allocation failed
 */
int createMinimumSpanningTree(const Graph *graph, Graph *mstGraph);

/* Returns the total weight of all edges in a graph. */
int getTotalWeight(const Graph *graph);

#endif