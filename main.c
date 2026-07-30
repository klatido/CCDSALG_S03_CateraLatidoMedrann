#include <stdio.h>

#include "graph.h"
#include "stack.h"

int main(void)
{
    Graph graph;
    Stack stack;

    initializeGraph(&graph, "G");

    addVertex(&graph, "Ken");
    addVertex(&graph, "Alek");
    addVertex(&graph, "Tristan");

    initializeStack(&stack);

    push(&stack, findVertex(&graph, "Ken"));
    push(&stack, findVertex(&graph, "Alek"));
    push(&stack, findVertex(&graph, "Tristan"));

    printf("%s\n", pop(&stack)->name);
    printf("%s\n", pop(&stack)->name);
    printf("%s\n", pop(&stack)->name);

    freeGraph(&graph);

    return 0;
}