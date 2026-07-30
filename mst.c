#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "mst.h"

/*
 * Copies all vertices from the linked list into an array.
 *
 * The caller is responsible for freeing the returned array.
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
 * Returns the index of a vertex inside the vertex array.
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
 * Finds the unvisited vertex with the smallest key value.
 */
static int findMinimumKeyVertex(const int key[],
                                const int included[],
                                int vertexCount)
{
    int minimum = INT_MAX;
    int minimumIndex = -1;
    int i;

    for (i = 0; i < vertexCount; i++) {
        if (!included[i] && key[i] < minimum) {
            minimum = key[i];
            minimumIndex = i;
        }
    }

    return minimumIndex;
}

int createMinimumSpanningTree(const Graph *graph, Graph *mstGraph)
{
    Vertex **vertices;
    int *key;
    int *parent;
    int *included;
    int vertexCount;
    int selectedVertex;
    int destinationIndex;
    int i;
    int iteration;

    if (graph == NULL ||
        mstGraph == NULL ||
        graph->vertexCount == 0) {

        return 0;
    }

    initializeGraph(mstGraph, "MST");

    vertexCount = graph->vertexCount;

    vertices = createVertexArray(graph);
    key = malloc(sizeof(int) * vertexCount);
    parent = malloc(sizeof(int) * vertexCount);
    included = calloc(vertexCount, sizeof(int));

    if (vertices == NULL ||
        key == NULL ||
        parent == NULL ||
        included == NULL) {

        free(vertices);
        free(key);
        free(parent);
        free(included);

        return 0;
    }

    /*
     * Add all original vertices to the MST graph.
     */
    for (i = 0; i < vertexCount; i++) {
        if (!addVertex(mstGraph, vertices[i]->name)) {
            free(vertices);
            free(key);
            free(parent);
            free(included);
            freeGraph(mstGraph);

            return 0;
        }

        key[i] = INT_MAX;
        parent[i] = -1;
    }

    /*
     * Begin Prim's Algorithm using the first
     * lexicographically sorted vertex.
     */
    key[0] = 0;

    for (iteration = 0;
         iteration < vertexCount;
         iteration++) {

        Vertex *currentVertex;
        EdgeNode *currentEdge;

        selectedVertex = findMinimumKeyVertex(
            key,
            included,
            vertexCount
        );

        /*
         * No reachable unvisited vertex was found.
         * Therefore, the graph is disconnected.
         */
        if (selectedVertex == -1) {
            free(vertices);
            free(key);
            free(parent);
            free(included);
            freeGraph(mstGraph);

            return 0;
        }

        included[selectedVertex] = 1;
        currentVertex = vertices[selectedVertex];
        currentEdge = currentVertex->edges;

        while (currentEdge != NULL) {
            destinationIndex = getVertexIndex(
                vertices,
                vertexCount,
                currentEdge->destination
            );

            if (destinationIndex != -1 &&
                !included[destinationIndex] &&
                currentEdge->weight < key[destinationIndex]) {

                key[destinationIndex] =
                    currentEdge->weight;

                parent[destinationIndex] =
                    selectedVertex;
            }

            currentEdge = currentEdge->next;
        }
    }

    /*
     * Add the selected MST edges.
     *
     * Vertex 0 has no parent because it is
     * the starting vertex.
     */
    for (i = 1; i < vertexCount; i++) {
        if (parent[i] == -1) {
            free(vertices);
            free(key);
            free(parent);
            free(included);
            freeGraph(mstGraph);

            return 0;
        }

        if (!addEdge(
                mstGraph,
                vertices[parent[i]]->name,
                vertices[i]->name,
                key[i])) {

            free(vertices);
            free(key);
            free(parent);
            free(included);
            freeGraph(mstGraph);

            return 0;
        }
    }

    free(vertices);
    free(key);
    free(parent);
    free(included);

    return 1;
}

int getTotalWeight(const Graph *graph)
{
    Vertex *vertex;
    EdgeNode *edge;
    int totalWeight = 0;

    if (graph == NULL) {
        return 0;
    }

    vertex = graph->vertices;

    while (vertex != NULL) {
        edge = vertex->edges;

        while (edge != NULL) {
            /*
             * Each undirected edge is stored twice.
             * Count it only when the source name comes
             * before the destination name.
             */
            if (strcmp(vertex->name,
                       edge->destination->name) < 0) {

                totalWeight += edge->weight;
            }

            edge = edge->next;
        }

        vertex = vertex->next;
    }

    return totalWeight;
}