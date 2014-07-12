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
        if (i != 0)
            strcat(dir, "/");
        strcat(dir, s->elems[i]);
    }

    return dir;
}
int main() {
    stack *s = stack_new();
    stack_push(s, ".");
    stack_push(s, "test_dir");
    stack_push(s, "test_dir_2");
    char *path = get_dir_path(s);

    printf("%s\n", path);
    free(path);
    empty_stack(s);
    return 0;
}
