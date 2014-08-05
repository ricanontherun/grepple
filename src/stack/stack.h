#ifndef STKINT_H
#define STKINT_H

#define STACK_MAX 100

typedef struct {
    int top; // Top of the stack
    char *elems[STACK_MAX];
} stack;

extern stack *stack_new(void);
extern void stack_push(stack *stack, char *s);
extern void stack_pop(stack *stack);
extern int is_stack_full(stack *stack);
extern int is_stack_empty(stack *stack);
extern void empty_stack(stack *stack);
#endif
