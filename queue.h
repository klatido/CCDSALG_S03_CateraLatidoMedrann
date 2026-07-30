#ifndef QUEUE_H
#define QUEUE_H

#include "graph.h"

#define QUEUE_CAPACITY 1000

typedef struct {
    Vertex *items[QUEUE_CAPACITY];
    int front;
    int rear;
    int size;
} Queue;

/* Initializes an empty queue. */
void initializeQueue(Queue *queue);

/* Returns 1 if the queue is empty. */
int isQueueEmpty(const Queue *queue);

/* Returns 1 if the queue is full. */
int isQueueFull(const Queue *queue);

/* Adds a vertex to the rear of the queue. */
int enqueue(Queue *queue, Vertex *vertex);

/* Removes and returns the front vertex. */
Vertex *dequeue(Queue *queue);

/* Returns the front vertex without removing it. */
Vertex *front(const Queue *queue);

#endif