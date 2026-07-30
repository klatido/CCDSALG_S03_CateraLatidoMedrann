#include <stdio.h>

#include "graph.h"
#include "traversal.h"

int main(void)
{
    Graph graph;

    initializeGraph(&graph, "G");

    addVertex(&graph, "Alek");
    addVertex(&graph, "Henry");
    addVertex(&graph, "Ken");
    addVertex(&graph, "Tristan");
    addVertex(&graph, "Kayenne");

    addEdge(&graph, "Alek", "Henry", 15);
    addEdge(&graph, "Alek", "Ken", 10);
    addEdge(&graph, "Henry", "Tristan", 5);
    addEdge(&graph, "Ken", "Tristan", 20);

    printf("BFS from Alek: ");
    breadthFirstSearch(&graph, "Alek");

    printf("DFS from Alek: ");
    depthFirstSearch(&graph, "Alek");

    printf("Path from Alek to Tristan: %d\n",
           pathExists(&graph, "Alek", "Tristan"));

    printf("Path from Alek to Kayenne: %d\n",
           pathExists(&graph, "Alek", "Kayenne"));

    freeGraph(&graph);

    return 0;
}