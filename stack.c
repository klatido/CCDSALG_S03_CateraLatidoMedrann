#include <stdlib.h>

#include "stack.h"

void initializeStack(Stack *stack)
{
    stack->top = -1;
}

int isStackEmpty(const Stack *stack)
{
    return stack->top == -1;
}

int isStackFull(const Stack *stack)
{
    return stack->top == STACK_CAPACITY - 1;
}

int push(Stack *stack, Vertex *vertex)
{
    if (isStackFull(stack)) {
        return 0;
    }

    stack->items[++stack->top] = vertex;

    return 1;
}

Vertex *pop(Stack *stack)
{
    if (isStackEmpty(stack)) {
        return NULL;
    }

    return stack->items[stack->top--];
}

Vertex *peek(const Stack *stack)
{
    if (isStackEmpty(stack)) {
        return NULL;
    }

    return stack->items[stack->top];
}