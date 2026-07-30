#include <stdio.h>

#include "graph.h"
#include "queue.h"

int main(void)
{
    Graph graph;
    Queue queue;

    initializeGraph(&graph, "G");

    addVertex(&graph, "Ken");
    addVertex(&graph, "Alek");
    addVertex(&graph, "Tristan");

    initializeQueue(&queue);

    enqueue(&queue, findVertex(&graph, "Ken"));
    enqueue(&queue, findVertex(&graph, "Alek"));
    enqueue(&queue, findVertex(&graph, "Tristan"));

    printf("%s\n", dequeue(&queue)->name);
    printf("%s\n", dequeue(&queue)->name);
    printf("%s\n", dequeue(&queue)->name);

    freeGraph(&graph);

    return 0;
}