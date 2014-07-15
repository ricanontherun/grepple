/*
    A custom stack implementation for grepple, my attempt at grep.
    Primarly used for directory path resolution.
 */
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Generic memory alloc macro
#define NEW(type) ((type *)malloc(sizeof(type)))

stack *stack_new() {
    stack *s = NEW(stack);

    if (!s) {
        fprintf(stderr, "stack error: Failed to allocate memory. Exiting program...\n");
        exit(0);
    }

    s->top = 0;
    s->alloc_top = 0;
    return s;
}

void stack_push(stack *stack, char *s) {
    if (!is_stack_full(stack)) {
        char *temp = strdup(s);
        stack->elems[stack->top++] = temp;
        stack->alloc_top++;
    } else
        fprintf(stderr, "stack error: stack is full\n");
}

char *stack_pop(stack *stack) {
    if (!is_stack_empty(stack))
        return stack->elems[--stack->top];
    else
        return NULL;
}

int is_stack_full(stack *stack) {
    return (stack->top) == STACK_MAX;
}

int is_stack_empty(stack *stack) {
    return stack->top == 0;
}

void empty_stack(stack *stack) {
    int i;

    for (i = 0; i < stack->alloc_top; i++) {
        free(stack->elems[i]);
    }
    free(stack);
    stack = NULL;
    return;
}
