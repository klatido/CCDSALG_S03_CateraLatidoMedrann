#ifndef HEAP_H
#define HEAP_H

#include "graph.h"

/*
 * Represents one entry in the min-heap.
 *
 * vertex   - graph vertex associated with the entry
 * distance - current tentative shortest distance
 */
typedef struct {
    Vertex *vertex;
    int distance;
} HeapNode;

/*
 * Dynamic binary min-heap.
 *
 * items    - dynamically allocated array of heap nodes
 * size     - current number of elements
 * capacity - current allocated capacity
 */
typedef struct {
    HeapNode *items;
    int size;
    int capacity;
} MinHeap;

/*
 * Initializes an empty min-heap.
 *
 * Returns:
 * 1 if successful
 * 0 if memory allocation fails
 */
int initializeHeap(MinHeap *heap, int initialCapacity);

/* Frees the dynamically allocated heap array. */
void freeHeap(MinHeap *heap);

/* Returns 1 if the heap is empty. */
int isHeapEmpty(const MinHeap *heap);

/*
 * Inserts a vertex-distance pair into the heap.
 *
 * Returns:
 * 1 if successful
 * 0 if memory allocation fails
 */
int insertHeap(MinHeap *heap, Vertex *vertex, int distance);

/*
 * Removes the node with the smallest distance.
 *
 * Returns:
 * 1 if successful
 * 0 if the heap is empty
 */
int extractMin(MinHeap *heap, HeapNode *minimumNode);

#endif