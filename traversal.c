#include <stdio.h>
#include <stdlib.h>

#include "traversal.h"
#include "stack.h"
#include "queue.h"

/*
 * Stores all graph vertices inside an array.
 * The returned array must be freed by the caller.
 */
static Vertex **getVertexArray(Graph *graph, int *count)
{
    Vertex **vertices;
    Vertex *current;
    int index = 0;

    *count = graph->vertexCount;

    if (*count == 0) {
        return NULL;
    }

    vertices = malloc(sizeof(Vertex *) * (*count));

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

/* Returns the index of a vertex inside the vertex array. */
static int getVertexIndex(Vertex **vertices, int count, Vertex *target)
{
    int i;

    for (i = 0; i < count; i++) {
        if (vertices[i] == target) {
            return i;
        }
    }

    return -1;
}

int breadthFirstSearch(Graph *graph, const char *startName)
{
    Vertex *start;
    Vertex *current;
    EdgeNode *edge;
    Vertex **vertices;
    int *visited;
    int vertexCount;
    int currentIndex;
    int neighborIndex;
    int firstPrinted = 1;
    Queue queue;

    start = findVertex(graph, startName);

    if (start == NULL) {
        return 0;
    }

    vertices = getVertexArray(graph, &vertexCount);

    if (vertices == NULL) {
        return 0;
    }

    visited = calloc(vertexCount, sizeof(int));

    if (visited == NULL) {
        free(vertices);
        return 0;
    }

    initializeQueue(&queue);

    currentIndex = getVertexIndex(vertices, vertexCount, start);
    visited[currentIndex] = 1;
    enqueue(&queue, start);

    while (!isQueueEmpty(&queue)) {
        current = dequeue(&queue);

        if (!firstPrinted) {
            printf(" ");
        }

        printf("%s", current->name);
        firstPrinted = 0;

        edge = current->edges;

        while (edge != NULL) {
            neighborIndex = getVertexIndex(
                vertices,
                vertexCount,
                edge->destination
            );

            if (neighborIndex != -1 && !visited[neighborIndex]) {
                visited[neighborIndex] = 1;
                enqueue(&queue, edge->destination);
            }

            edge = edge->next;
        }
    }

    printf("\n");

    free(visited);
    free(vertices);

    return 1;
}

int depthFirstSearch(Graph *graph, const char *startName)
{
    Vertex *start;
    Vertex *current;
    EdgeNode *edge;
    Vertex **vertices;
    Vertex **neighbors;
    int *visited;
    int vertexCount;
    int currentIndex;
    int neighborIndex;
    int neighborCount;
    int i;
    int firstPrinted = 1;
    Stack stack;

    start = findVertex(graph, startName);

    if (start == NULL) {
        return 0;
    }

    vertices = getVertexArray(graph, &vertexCount);

    if (vertices == NULL) {
        return 0;
    }

    visited = calloc(vertexCount, sizeof(int));
    neighbors = malloc(sizeof(Vertex *) * vertexCount);

    if (visited == NULL || neighbors == NULL) {
        free(visited);
        free(neighbors);
        free(vertices);
        return 0;
    }

    initializeStack(&stack);
    push(&stack, start);

    while (!isStackEmpty(&stack)) {
        current = pop(&stack);

        currentIndex = getVertexIndex(
            vertices,
            vertexCount,
            current
        );

        if (currentIndex == -1 || visited[currentIndex]) {
            continue;
        }

        visited[currentIndex] = 1;

        if (!firstPrinted) {
            printf(" ");
        }

        printf("%s", current->name);
        firstPrinted = 0;

        /*
         * The adjacency list is alphabetical.
         * We collect neighbors first, then push them in reverse order.
         * This makes DFS visit alphabetically earlier vertices first.
         */
        neighborCount = 0;
        edge = current->edges;

        while (edge != NULL) {
            neighborIndex = getVertexIndex(
                vertices,
                vertexCount,
                edge->destination
            );

            if (neighborIndex != -1 && !visited[neighborIndex]) {
                neighbors[neighborCount++] = edge->destination;
            }

            edge = edge->next;
        }

        for (i = neighborCount - 1; i >= 0; i--) {
            push(&stack, neighbors[i]);
        }
    }

    printf("\n");

    free(neighbors);
    free(visited);
    free(vertices);

    return 1;
}

int pathExists(Graph *graph, const char *startName, const char *endName)
{
    Vertex *start;
    Vertex *end;
    Vertex *current;
    EdgeNode *edge;
    Vertex **vertices;
    int *visited;
    int vertexCount;
    int currentIndex;
    int neighborIndex;
    Queue queue;

    start = findVertex(graph, startName);
    end = findVertex(graph, endName);

    if (start == NULL || end == NULL) {
        return 0;
    }

    if (start == end) {
        return 1;
    }

    vertices = getVertexArray(graph, &vertexCount);

    if (vertices == NULL) {
        return 0;
    }

    visited = calloc(vertexCount, sizeof(int));

    if (visited == NULL) {
        free(vertices);
        return 0;
    }

    initializeQueue(&queue);

    currentIndex = getVertexIndex(vertices, vertexCount, start);
    visited[currentIndex] = 1;
    enqueue(&queue, start);

    while (!isQueueEmpty(&queue)) {
        current = dequeue(&queue);
        edge = current->edges;

        while (edge != NULL) {
            if (edge->destination == end) {
                free(visited);
                free(vertices);
                return 1;
            }

            neighborIndex = getVertexIndex(
                vertices,
                vertexCount,
                edge->destination
            );

            if (neighborIndex != -1 && !visited[neighborIndex]) {
                visited[neighborIndex] = 1;
                enqueue(&queue, edge->destination);
            }

            edge = edge->next;
        }
    }

    free(visited);
    free(vertices);

    return 0;
}