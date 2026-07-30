#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "shortpathb.h"
#include "heap.h"

/*
 * Copies all graph vertices into an array.
 *
 * Since the graph's vertex linked list is maintained
 * lexicographically, the resulting array is also
 * lexicographically ordered.
 */
static Vertex **createVertexArray(const Graph *graph)
{
    Vertex **vertices;
    Vertex *current;
    int index = 0;

    if (graph == NULL || graph->vertexCount == 0) {
        return NULL;
    }

    vertices = malloc(
        sizeof(Vertex *) * graph->vertexCount
    );

    if (vertices == NULL) {
        return NULL;
    }

    current = graph->vertices;

    while (current != NULL) {
        vertices[index++] = current;
        current = current->next;
    }

    return vertices;
}

/*
 * Finds the array index of a vertex.
 */
static int getVertexIndex(Vertex **vertices,
                          int vertexCount,
                          Vertex *target)
{
    int i;

    for (i = 0; i < vertexCount; i++) {
        if (vertices[i] == target) {
            return i;
        }
    }

    return -1;
}

/*
 * Determines whether a new parent should be preferred
 * when two possible paths have equal total distances.
 *
 * The lexicographically smaller predecessor is selected
 * to provide deterministic output.
 */
static int shouldReplaceEqualParent(Vertex **vertices,
                                    int currentParentIndex,
                                    int proposedParentIndex)
{
    if (currentParentIndex == -1) {
        return 1;
    }

    return strcmp(
        vertices[proposedParentIndex]->name,
        vertices[currentParentIndex]->name
    ) < 0;
}

int printShortestPath(const Graph *graph,
                      const char *startName,
                      const char *endName)
{
    Vertex *start;
    Vertex *end;
    Vertex **vertices;
    Vertex **path;
    int *distance;
    int *parent;
    int vertexCount;
    int startIndex;
    int endIndex;
    int currentIndex;
    int destinationIndex;
    int newDistance;
    int pathLength = 0;
    int pathIndex;
    int i;
    MinHeap heap;
    HeapNode minimumNode;

    if (graph == NULL ||
        startName == NULL ||
        endName == NULL ||
        graph->vertexCount == 0) {

        return 0;
    }

    start = findVertex(graph, startName);
    end = findVertex(graph, endName);

    if (start == NULL || end == NULL) {
        return 0;
    }

    vertexCount = graph->vertexCount;

    vertices = createVertexArray(graph);
    distance = malloc(sizeof(int) * vertexCount);
    parent = malloc(sizeof(int) * vertexCount);
    path = malloc(sizeof(Vertex *) * vertexCount);

    if (vertices == NULL ||
        distance == NULL ||
        parent == NULL ||
        path == NULL) {

        free(vertices);
        free(distance);
        free(parent);
        free(path);

        return 0;
    }

    if (!initializeHeap(&heap, vertexCount)) {
        free(vertices);
        free(distance);
        free(parent);
        free(path);

        return 0;
    }

    startIndex = getVertexIndex(
        vertices,
        vertexCount,
        start
    );

    endIndex = getVertexIndex(
        vertices,
        vertexCount,
        end
    );

    if (startIndex == -1 || endIndex == -1) {
        freeHeap(&heap);
        free(vertices);
        free(distance);
        free(parent);
        free(path);

        return 0;
    }

    /*
     * Initialize every vertex as unreachable.
     */
    for (i = 0; i < vertexCount; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[startIndex] = 0;

    if (!insertHeap(&heap, start, 0)) {
        freeHeap(&heap);
        free(vertices);
        free(distance);
        free(parent);
        free(path);

        return 0;
    }

    /*
     * Dijkstra's Algorithm
     */
    while (!isHeapEmpty(&heap)) {
        EdgeNode *edge;

        extractMin(&heap, &minimumNode);

        currentIndex = getVertexIndex(
            vertices,
            vertexCount,
            minimumNode.vertex
        );

        if (currentIndex == -1) {
            continue;
        }

        /*
         * Multiple entries for the same vertex may exist
         * in the heap. Ignore entries containing an older
         * and larger tentative distance.
         */
        if (minimumNode.distance != distance[currentIndex]) {
            continue;
        }

        /*
         * The destination has been removed with its
         * minimum distance, so the shortest path is final.
         */
        if (currentIndex == endIndex) {
            break;
        }

        edge = minimumNode.vertex->edges;

        while (edge != NULL) {
            destinationIndex = getVertexIndex(
                vertices,
                vertexCount,
                edge->destination
            );

            if (destinationIndex != -1 &&
                distance[currentIndex] != INT_MAX &&
                distance[currentIndex] <=
                    INT_MAX - edge->weight) {

                newDistance =
                    distance[currentIndex] +
                    edge->weight;

                if (newDistance <
                    distance[destinationIndex]) {

                    distance[destinationIndex] =
                        newDistance;

                    parent[destinationIndex] =
                        currentIndex;

                    if (!insertHeap(
                            &heap,
                            edge->destination,
                            newDistance)) {

                        freeHeap(&heap);
                        free(vertices);
                        free(distance);
                        free(parent);
                        free(path);

                        return 0;
                    }
                }

                /*
                 * Equal-distance paths are resolved using
                 * the lexicographically smaller predecessor.
                 */
                else if (
                    newDistance ==
                        distance[destinationIndex] &&
                    destinationIndex != startIndex &&
                    shouldReplaceEqualParent(
                        vertices,
                        parent[destinationIndex],
                        currentIndex)) {

                    parent[destinationIndex] =
                        currentIndex;
                }
            }

            edge = edge->next;
        }
    }

    /*
     * The destination was not reached.
     */
    if (distance[endIndex] == INT_MAX) {
        freeHeap(&heap);
        free(vertices);
        free(distance);
        free(parent);
        free(path);

        return 0;
    }

    /*
     * Reconstruct the shortest path backward:
     * destination -> ... -> start
     */
    pathIndex = endIndex;

    while (pathIndex != -1) {
        path[pathLength++] = vertices[pathIndex];

        if (pathIndex == startIndex) {
            break;
        }

        pathIndex = parent[pathIndex];
    }

    /*
     * The parent chain failed to reach the start.
     */
    if (pathLength == 0 ||
        path[pathLength - 1] != start) {

        freeHeap(&heap);
        free(vertices);
        free(distance);
        free(parent);
        free(path);

        return 0;
    }

    /*
     * Print the reconstructed path in reverse order:
     * start -> ... -> destination
     */
    for (i = pathLength - 1; i >= 0; i--) {
        printf("%s", path[i]->name);

        if (i > 0) {
            printf(" -> ");
        }
    }

    printf("; Total edge cost = %d\n",
           distance[endIndex]);

    freeHeap(&heap);
    free(vertices);
    free(distance);
    free(parent);
    free(path);

    return 1;
}