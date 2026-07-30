#include <stdio.h>

#include "graph.h"

int main(void)
{
    Graph graph;

    initializeGraph(&graph, "G");

    addVertex(&graph, "Ken");
    addVertex(&graph, "Alek");
    addVertex(&graph, "Tristan");
    addVertex(&graph, "Henry");

    addEdge(&graph, "Ken", "Alek", 10);
    addEdge(&graph, "Ken", "Tristan", 20);
    addEdge(&graph, "Alek", "Henry", 15);
    addEdge(&graph, "Tristan", "Henry", 5);

    printf("Degree of Ken: %d\n", getDegree(&graph, "Ken"));
    printf("Degree of Henry: %d\n", getDegree(&graph, "Henry"));

    printf("Ken-Alek edge: %d\n",
           edgeExists(&graph, "Ken", "Alek"));

    printf("Ken-Henry edge: %d\n",
           edgeExists(&graph, "Ken", "Henry"));

    printf("\n");

    printGraph(&graph);

    freeGraph(&graph);

    return 0;
}