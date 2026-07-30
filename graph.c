#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

/*
 * Copies a vertex or graph name safely.
 */
static void copyName(char destination[], const char *source)
{
    strncpy(destination, source, MAX_NAME_LENGTH);
    destination[MAX_NAME_LENGTH] = '\0';
}

/*
 * Creates a new vertex.
 */
static Vertex *createVertex(const char *name)
{
    Vertex *newVertex = malloc(sizeof(Vertex));

    if (newVertex == NULL) {
        return NULL;
    }

    copyName(newVertex->name, name);
    newVertex->edges = NULL;
    newVertex->next = NULL;

    return newVertex;
}

/*
 * Creates a new adjacency-list node.
 */
static EdgeNode *createEdgeNode(Vertex *destination, int weight)
{
    EdgeNode *newEdge = malloc(sizeof(EdgeNode));

    if (newEdge == NULL) {
        return NULL;
    }

    newEdge->destination = destination;
    newEdge->weight = weight;
    newEdge->next = NULL;

    return newEdge;
}

/*
 * Inserts an edge node into an adjacency list in
 * lexicographical order based on the destination name.
 */
static void insertEdgeSorted(Vertex *source, EdgeNode *newEdge)
{
    EdgeNode *current;

    if (source->edges == NULL ||
        strcmp(newEdge->destination->name,
               source->edges->destination->name) < 0) {

        newEdge->next = source->edges;
        source->edges = newEdge;
        return;
    }

    current = source->edges;

    while (current->next != NULL &&
           strcmp(current->next->destination->name,
                  newEdge->destination->name) < 0) {

        current = current->next;
    }

    newEdge->next = current->next;
    current->next = newEdge;
}

void initializeGraph(Graph *graph, const char *name)
{
    if (graph == NULL) {
        return;
    }

    if (name == NULL || name[0] == '\0') {
        copyName(graph->name, "G");
    } else {
        copyName(graph->name, name);
    }

    graph->vertices = NULL;
    graph->vertexCount = 0;
    graph->edgeCount = 0;
}

Vertex *findVertex(const Graph *graph, const char *name)
{
    Vertex *current;

    if (graph == NULL || name == NULL) {
        return NULL;
    }

    current = graph->vertices;

    while (current != NULL) {
        int comparison = strcmp(current->name, name);

        if (comparison == 0) {
            return current;
        }

        /*
         * Vertices are stored lexicographically.
         * If the current name is already greater than
         * the target, the target cannot appear later.
         */
        if (comparison > 0) {
            return NULL;
        }

        current = current->next;
    }

    return NULL;
}

int addVertex(Graph *graph, const char *name)
{
    Vertex *newVertex;
    Vertex *current;

    if (graph == NULL ||
        name == NULL ||
        name[0] == '\0' ||
        strlen(name) > MAX_NAME_LENGTH) {

        return 0;
    }

    if (findVertex(graph, name) != NULL) {
        return 0;
    }

    newVertex = createVertex(name);

    if (newVertex == NULL) {
        return 0;
    }

    /*
     * Insert at the beginning if the graph is empty
     * or the new name comes before the first vertex.
     */
    if (graph->vertices == NULL ||
        strcmp(name, graph->vertices->name) < 0) {

        newVertex->next = graph->vertices;
        graph->vertices = newVertex;
        graph->vertexCount++;

        return 1;
    }

    current = graph->vertices;

    /*
     * Find the correct lexicographical position.
     */
    while (current->next != NULL &&
           strcmp(current->next->name, name) < 0) {

        current = current->next;
    }

    newVertex->next = current->next;
    current->next = newVertex;

    graph->vertexCount++;

    return 1;
}

int edgeExists(const Graph *graph,
               const char *name1,
               const char *name2)
{
    Vertex *source;
    Vertex *destination;
    EdgeNode *current;

    if (graph == NULL || name1 == NULL || name2 == NULL) {
        return 0;
    }

    source = findVertex(graph, name1);
    destination = findVertex(graph, name2);

    if (source == NULL || destination == NULL) {
        return 0;
    }

    current = source->edges;

    while (current != NULL) {
        int comparison =
            strcmp(current->destination->name, destination->name);

        if (comparison == 0) {
            return 1;
        }

        /*
         * The adjacency list is sorted.
         * Stop once names exceed the target.
         */
        if (comparison > 0) {
            return 0;
        }

        current = current->next;
    }

    return 0;
}

int addEdge(Graph *graph,
            const char *name1,
            const char *name2,
            int weight)
{
    Vertex *vertex1;
    Vertex *vertex2;
    EdgeNode *edgeToVertex2;
    EdgeNode *edgeToVertex1;

    if (graph == NULL ||
        name1 == NULL ||
        name2 == NULL ||
        weight < 1 ||
        weight > 100) {

        return 0;
    }

    /*
     * Self-loops are not added.
     */
    if (strcmp(name1, name2) == 0) {
        return 0;
    }

    vertex1 = findVertex(graph, name1);
    vertex2 = findVertex(graph, name2);

    /*
     * Both vertices must already exist.
     */
    if (vertex1 == NULL || vertex2 == NULL) {
        return 0;
    }

    /*
     * Prevent duplicate edges.
     */
    if (edgeExists(graph, name1, name2)) {
        return 0;
    }

    /*
     * Because the graph is undirected, create two
     * adjacency-list entries:
     *
     * vertex1 -> vertex2
     * vertex2 -> vertex1
     */
    edgeToVertex2 = createEdgeNode(vertex2, weight);

    if (edgeToVertex2 == NULL) {
        return 0;
    }

    edgeToVertex1 = createEdgeNode(vertex1, weight);

    if (edgeToVertex1 == NULL) {
        free(edgeToVertex2);
        return 0;
    }

    insertEdgeSorted(vertex1, edgeToVertex2);
    insertEdgeSorted(vertex2, edgeToVertex1);

    /*
     * Count the undirected edge only once.
     */
    graph->edgeCount++;

    return 1;
}

int getDegree(const Graph *graph, const char *name)
{
    Vertex *vertex;
    EdgeNode *current;
    int degree = 0;

    if (graph == NULL || name == NULL) {
        return -1;
    }

    vertex = findVertex(graph, name);

    if (vertex == NULL) {
        return -1;
    }

    current = vertex->edges;

    while (current != NULL) {
        degree++;
        current = current->next;
    }

    return degree;
}

void printGraph(const Graph *graph)
{
    Vertex *vertex;
    EdgeNode *edge;
    int printedVertices = 0;
    int printedEdges = 0;

    if (graph == NULL) {
        return;
    }

    printf("%s = (V,E)\n", graph->name);

    /*
     * Print the vertex set.
     */
    printf("V = {");

    vertex = graph->vertices;

    while (vertex != NULL) {
        if (printedVertices > 0) {
            printf(", ");
        }

        printf("%s", vertex->name);

        printedVertices++;
        vertex = vertex->next;
    }

    printf("}\n");

    /*
     * Print the edge set.
     */
    printf("E = {\n");

    vertex = graph->vertices;

    while (vertex != NULL) {
        edge = vertex->edges;

        while (edge != NULL) {
            /*
             * An undirected edge is stored twice.
             * Print it only when the source vertex comes
             * before the destination lexicographically.
             */
            if (strcmp(vertex->name,
                       edge->destination->name) < 0) {

                if (printedEdges > 0) {
                    printf(",\n");
                }

                printf("(%s, %s, %d)",
                       vertex->name,
                       edge->destination->name,
                       edge->weight);

                printedEdges++;
            }

            edge = edge->next;
        }

        vertex = vertex->next;
    }

    if (printedEdges > 0) {
        printf("\n");
    }

    printf("}\n");
}

void freeGraph(Graph *graph)
{
    Vertex *currentVertex;
    Vertex *nextVertex;

    if (graph == NULL) {
        return;
    }

    currentVertex = graph->vertices;

    while (currentVertex != NULL) {
        EdgeNode *currentEdge = currentVertex->edges;

        while (currentEdge != NULL) {
            EdgeNode *nextEdge = currentEdge->next;

            free(currentEdge);
            currentEdge = nextEdge;
        }

        nextVertex = currentVertex->next;

        free(currentVertex);
        currentVertex = nextVertex;
    }

    graph->vertices = NULL;
    graph->vertexCount = 0;
    graph->edgeCount = 0;
}