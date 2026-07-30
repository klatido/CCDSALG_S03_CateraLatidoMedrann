#ifndef SPB_H
#define SPB_H

#include "graph.h"

/*
 * Computes and prints the shortest path between two vertices
 * using Dijkstra's Algorithm and a binary min-heap.
 *
 * Output format:
 * vertex1 -> vertex2 -> ... -> destination;
 * Total edge cost = weight
 *
 * The complete output is printed on one line.
 *
 * Returns:
 * 1 if a shortest path was found and printed
 * 0 if either vertex does not exist, no path exists,
 *   or memory allocation fails
 */
int printShortestPath(const Graph *graph,
                      const char *startName,
                      const char *endName);

#endif