#ifndef GREPPLE_STACK_H 
#define GREPPLE_STACK_H 

struct stack {
    int top;
    size_t max;
    char **elems;
};

extern struct stack *stack_new(size_t size);
extern void stack_push(struct stack *stack, char *s);
extern void stack_pop(struct stack *stack);
extern int is_stack_full(struct stack *stack);
extern int is_stack_empty(struct stack *stack);
extern void empty_stack(struct stack *stack);
#endif
