#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "stdlib.h"

char *dir;
char *get_dir_path(stack *s) {
    int i;
    dir = (char *)malloc(strlen(s->elems[0]));
    int str_len = 1;

    for (i = 0; i < s->top; i++) {
        str_len++;
        dir = (char *) realloc(dir, (str_len * sizeof(s->elems[i])) + 1);
        strcat(dir, s->elems[i]);
        strcat(dir, "/");
    }

    return dir;
}
int main() {
    char *curr_path;
    stack *stk = stack_new();

    stack_push(stk, ".");
    curr_path = get_dir_path(stk);

    stack_push(stk, "app");
    curr_path = get_dir_path(stk);

    stack_push(stk, "controllers");
    curr_path = get_dir_path(stk);

    empty_stack(stk);
    free(curr_path);
    return 0;
}
