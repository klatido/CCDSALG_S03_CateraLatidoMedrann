#include <stddef.h>

#include "queue.h"

void initializeQueue(Queue *queue)
{
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
}

int isQueueEmpty(const Queue *queue)
{
    return queue->size == 0;
}

int isQueueFull(const Queue *queue)
{
    return queue->size == QUEUE_CAPACITY;
}

int enqueue(Queue *queue, Vertex *vertex)
{
    if (isQueueFull(queue)) {
        return 0;
    }

    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;
    queue->items[queue->rear] = vertex;
    queue->size++;

    return 1;
}

Vertex *dequeue(Queue *queue)
{
    Vertex *vertex;

    if (isQueueEmpty(queue)) {
        return NULL;
    }

    vertex = queue->items[queue->front];

    queue->front = (queue->front + 1) % QUEUE_CAPACITY;
    queue->size--;

    return vertex;
}

Vertex *front(const Queue *queue)
{
    if (isQueueEmpty(queue)) {
        return NULL;
    }

    return queue->items[queue->front];
}