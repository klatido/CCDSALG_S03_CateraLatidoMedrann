#include <stdio.h>

#include "graph.h"
#include "mst.h"

int main(void)
{
    Graph graph;
    Graph mst;

    initializeGraph(&graph, "G");

    addVertex(&graph, "A");
    addVertex(&graph, "B");
    addVertex(&graph, "C");
    addVertex(&graph, "D");
    addVertex(&graph, "E");

    addEdge(&graph, "A", "B", 2);
    addEdge(&graph, "A", "C", 3);
    addEdge(&graph, "B", "C", 1);
    addEdge(&graph, "B", "D", 4);
    addEdge(&graph, "C", "D", 5);
    addEdge(&graph, "C", "E", 6);
    addEdge(&graph, "D", "E", 7);

    printf("Original Graph:\n");
    printGraph(&graph);

    printf("\n");

    if (createMinimumSpanningTree(&graph, &mst)) {
        printf("Minimum Spanning Tree:\n");
        printGraph(&mst);

        printf(
            "Total MST Weight: %d\n",
            getTotalWeight(&mst)
        );

        freeGraph(&mst);
    } else {
        printf(
            "Minimum Spanning Tree cannot be created.\n"
        );
    }

    freeGraph(&graph);

    return 0;
}