#include <stdio.h>

#include "graph.h"
#include "traversal.h"
#include "mst.h"

int main(void)
{
    Graph graph;
    int command;

    initializeGraph(&graph, "G");

    while (scanf("%d", &command) == 1) {

        if (command == 1) {
            char name[MAX_NAME_LENGTH + 1];

            if (scanf("%256s", name) == 1) {
                addVertex(&graph, name);
            }
        }

        else if (command == 2) {
            char name1[MAX_NAME_LENGTH + 1];
            char name2[MAX_NAME_LENGTH + 1];
            int weight;

            if (scanf("%256s %256s %d",
                      name1,
                      name2,
                      &weight) == 3) {

                addEdge(
                    &graph,
                    name1,
                    name2,
                    weight
                );
            }
        }

        else if (command == 3) {
            char name[MAX_NAME_LENGTH + 1];
            int degree;

            if (scanf("%256s", name) == 1) {
                degree = getDegree(&graph, name);
                printf("%d\n", degree);
            }
        }

        else if (command == 4) {
            char name1[MAX_NAME_LENGTH + 1];
            char name2[MAX_NAME_LENGTH + 1];

            if (scanf("%256s %256s",
                      name1,
                      name2) == 2) {

                printf(
                    "%d\n",
                    edgeExists(
                        &graph,
                        name1,
                        name2
                    )
                );
            }
        }

        else if (command == 5) {
            char name[MAX_NAME_LENGTH + 1];

            if (scanf("%256s", name) == 1) {
                breadthFirstSearch(
                    &graph,
                    name
                );
            }
        }

        else if (command == 6) {
            char name[MAX_NAME_LENGTH + 1];

            if (scanf("%256s", name) == 1) {
                depthFirstSearch(
                    &graph,
                    name
                );
            }
        }

        else if (command == 7) {
            char name1[MAX_NAME_LENGTH + 1];
            char name2[MAX_NAME_LENGTH + 1];

            if (scanf("%256s %256s",
                      name1,
                      name2) == 2) {

                printf(
                    "%d\n",
                    pathExists(
                        &graph,
                        name1,
                        name2
                    )
                );
            }
        }

        else if (command == 8) {
            Graph mst;

            if (createMinimumSpanningTree(
                    &graph,
                    &mst)) {

                printGraph(&mst);
                freeGraph(&mst);
            }
        }

        else if (command == 9) {
            /*
             * BONUS: Shortest Path
             *
             * The two names are still read so the input
             * stream remains synchronized.
             */
            char name1[MAX_NAME_LENGTH + 1];
            char name2[MAX_NAME_LENGTH + 1];

            scanf("%256s %256s", name1, name2);
        }

        else if (command == 10) {
            printGraph(&graph);
        }

        else if (command == 11) {
            break;
        }
    }

    freeGraph(&graph);

    return 0;
}