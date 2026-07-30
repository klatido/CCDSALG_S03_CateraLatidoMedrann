#include <stdlib.h>
#include <string.h>

#include "heap.h"

/*
 * Compares two heap nodes.
 *
 * A node with a smaller distance has higher priority.
 * If distances are equal, the vertex with the
 * lexicographically smaller name has higher priority.
 */
static int hasHigherPriority(const HeapNode *first,
                             const HeapNode *second)
{
    if (first->distance < second->distance) {
        return 1;
    }

    if (first->distance > second->distance) {
        return 0;
    }

    return strcmp(first->vertex->name,
                  second->vertex->name) < 0;
}

/* Swaps two heap nodes. */
static void swapHeapNodes(HeapNode *first, HeapNode *second)
{
    HeapNode temporary = *first;
    *first = *second;
    *second = temporary;
}

/*
 * Doubles the current capacity of the heap.
 */
static int resizeHeap(MinHeap *heap)
{
    HeapNode *resizedItems;
    int newCapacity;

    if (heap->capacity == 0) {
        newCapacity = 1;
    } else {
        newCapacity = heap->capacity * 2;
    }

    resizedItems = realloc(
        heap->items,
        sizeof(HeapNode) * newCapacity
    );

    if (resizedItems == NULL) {
        return 0;
    }

    heap->items = resizedItems;
    heap->capacity = newCapacity;

    return 1;
}

int initializeHeap(MinHeap *heap, int initialCapacity)
{
    if (heap == NULL) {
        return 0;
    }

    if (initialCapacity < 1) {
        initialCapacity = 1;
    }

    heap->items = malloc(
        sizeof(HeapNode) * initialCapacity
    );

    if (heap->items == NULL) {
        heap->size = 0;
        heap->capacity = 0;
        return 0;
    }

    heap->size = 0;
    heap->capacity = initialCapacity;

    return 1;
}

void freeHeap(MinHeap *heap)
{
    if (heap == NULL) {
        return;
    }

    free(heap->items);

    heap->items = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

int isHeapEmpty(const MinHeap *heap)
{
    return heap == NULL || heap->size == 0;
}

int insertHeap(MinHeap *heap, Vertex *vertex, int distance)
{
    int currentIndex;
    int parentIndex;

    if (heap == NULL || vertex == NULL) {
        return 0;
    }

    if (heap->size == heap->capacity) {
        if (!resizeHeap(heap)) {
            return 0;
        }
    }

    currentIndex = heap->size;

    heap->items[currentIndex].vertex = vertex;
    heap->items[currentIndex].distance = distance;

    heap->size++;

    /*
     * Move the inserted node upward until the
     * min-heap property is restored.
     */
    while (currentIndex > 0) {
        parentIndex = (currentIndex - 1) / 2;

        if (!hasHigherPriority(
                &heap->items[currentIndex],
                &heap->items[parentIndex])) {

            break;
        }

        swapHeapNodes(
            &heap->items[currentIndex],
            &heap->items[parentIndex]
        );

        currentIndex = parentIndex;
    }

    return 1;
}

int extractMin(MinHeap *heap, HeapNode *minimumNode)
{
    int currentIndex;
    int leftChildIndex;
    int rightChildIndex;
    int highestPriorityIndex;

    if (heap == NULL ||
        minimumNode == NULL ||
        heap->size == 0) {

        return 0;
    }

    *minimumNode = heap->items[0];

    heap->size--;

    /*
     * If the removed node was the final node,
     * no heap restoration is needed.
     */
    if (heap->size == 0) {
        return 1;
    }

    heap->items[0] = heap->items[heap->size];

    /*
     * Move the replacement node downward until
     * the min-heap property is restored.
     */
    currentIndex = 0;

    while (1) {
        leftChildIndex = (2 * currentIndex) + 1;
        rightChildIndex = (2 * currentIndex) + 2;
        highestPriorityIndex = currentIndex;

        if (leftChildIndex < heap->size &&
            hasHigherPriority(
                &heap->items[leftChildIndex],
                &heap->items[highestPriorityIndex])) {

            highestPriorityIndex = leftChildIndex;
        }

        if (rightChildIndex < heap->size &&
            hasHigherPriority(
                &heap->items[rightChildIndex],
                &heap->items[highestPriorityIndex])) {

            highestPriorityIndex = rightChildIndex;
        }

        if (highestPriorityIndex == currentIndex) {
            break;
        }

        swapHeapNodes(
            &heap->items[currentIndex],
            &heap->items[highestPriorityIndex]
        );

        currentIndex = highestPriorityIndex;
    }

    return 1;
}