#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NAME_LENGTH 256

/*
 * Forward declaration.
 * This allows EdgeNode to store a pointer to a Vertex
 * even before the complete Vertex structure is declared.
 */
typedef struct Vertex Vertex;

/*
 * Represents one connection in a vertex's adjacency list.
 *
 * destination - the vertex connected to the current vertex
 * weight      - the weight of the edge
 * next        - pointer to the next adjacent vertex
 */
typedef struct EdgeNode {
    Vertex *destination;
    int weight;
    struct EdgeNode *next;
} EdgeNode;

/*
 * Represents one vertex in the graph.
 *
 * name  - unique name of the vertex
 * edges - head of the vertex's adjacency list
 * next  - pointer to the next vertex in the graph
 */
struct Vertex {
    char name[MAX_NAME_LENGTH + 1];
    EdgeNode *edges;
    Vertex *next;
};

/*
 * Represents the complete undirected, weighted graph.
 *
 * name        - name printed in the graph definition
 * vertices    - head of the linked list of vertices
 * vertexCount - number of vertices
 * edgeCount   - number of undirected edges
 */
typedef struct {
    char name[MAX_NAME_LENGTH + 1];
    Vertex *vertices;
    int vertexCount;
    int edgeCount;
} Graph;

/* Initializes an empty graph. */
void initializeGraph(Graph *graph, const char *name);

/* Searches for a vertex using its name. */
Vertex *findVertex(const Graph *graph, const char *name);

/*
 * Adds a new vertex.
 *
 * Returns:
 * 1 if the vertex was added successfully
 * 0 if the vertex already exists or memory allocation failed
 */
int addVertex(Graph *graph, const char *name);

/*
 * Adds an undirected weighted edge between two existing vertices.
 *
 * Returns:
 * 1 if the edge was added successfully
 * 0 if either vertex does not exist, the edge already exists,
 *   the vertices are the same, the weight is invalid,
 *   or memory allocation failed
 */
int addEdge(Graph *graph,
            const char *name1,
            const char *name2,
            int weight);

/*
 * Returns the degree of a vertex.
 *
 * Returns:
 * degree of the vertex if it exists
 * -1 if the vertex does not exist
 */
int getDegree(const Graph *graph, const char *name);

/*
 * Checks whether two vertices are directly connected.
 *
 * Returns:
 * 1 if an edge exists
 * 0 if no edge exists or either vertex does not exist
 */
int edgeExists(const Graph *graph,
               const char *name1,
               const char *name2);

/* Prints the graph using the required graph-definition format. */
void printGraph(const Graph *graph);

/* Frees all dynamically allocated graph memory. */
void freeGraph(Graph *graph);

#endif