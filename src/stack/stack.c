#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

#define NEW(type) (malloc(sizeof(type)))

/**
 *  Create a new stack interface.
 */
struct stack *stack_new(size_t size) {
    struct stack *s = NEW(struct stack);

    if (!s) {
        fprintf(stderr, "stack error: Failed to allocate memory. Exiting program...\n");
    }
    
    s->elems = calloc(sizeof(char *) * size, sizeof(char *));
    s->max = size;
    s->top = 0;

    return s;
}

/**
 *  Push a new string on to the stack
 *
 *  @param stack (stack *) Stack
 *  @param s (char *) String to push on the stack
 */
void stack_push(struct stack *stack, char *s) {
    if (!is_stack_full(stack)) {
        char *temp = strdup(s);
        stack->elems[stack->top++] = temp;
    } else {
        fprintf(stderr, "stack error: stack is full\n");
    }
}

/**
 *  Pop a value off of the stack. This does NOT return a value, as a normal stack implementation does.
 *  For the purposes of grepple, it doesn't need to.
 *
 *  @param stack (stack *) Stack
 */
void stack_pop(struct stack *stack) {
    if (!is_stack_empty(stack)) {
        free(stack->elems[--stack->top]);
    }
}

/**
 *  Is the stack full?
 *
 *  @param stack (stack *) stack
 */
int is_stack_full(struct stack *stack) {
    return (stack->top) == stack->max;
}

/**
 *  Is the stack empty?
 *
 *  @param stack (stack *) stack
 */
int is_stack_empty(struct stack *stack) {
    return stack->top == 0;
}

/**
 *  Completely empty and free a stack.
 *
 *  @param stack (stack *) stack
 */
void empty_stack(struct stack *stack) {
    if (!is_stack_empty(stack)) {
        int i;

        for (i = 0; i < stack->top; i++) {
            free(stack->elems[i]);
        }
    }
    
    free(stack->elems);
    free(stack);

    stack = NULL;
}
