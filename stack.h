#ifndef STACK_H
#define STACK_H

#include "graph.h"

#define STACK_CAPACITY 1000

typedef struct {
    Vertex *items[STACK_CAPACITY];
    int top;
} Stack;

/* Initializes the stack. */
void initializeStack(Stack *stack);

/* Returns 1 if empty, 0 otherwise. */
int isStackEmpty(const Stack *stack);

/* Returns 1 if full, 0 otherwise. */
int isStackFull(const Stack *stack);

/* Pushes a vertex onto the stack. */
int push(Stack *stack, Vertex *vertex);

/* Removes the top vertex. */
Vertex *pop(Stack *stack);

/* Returns the top vertex without removing it. */
Vertex *peek(const Stack *stack);

#endif