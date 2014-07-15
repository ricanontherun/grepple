#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZEOF(n) (sizeof(n) / sizeof(n[0]))
stack *s;

char *get_dir_path(stack *s) {
    int i;
    char *current_path = (char *)malloc(strlen(s->elems[0]));
    int str_len = 1;

    if (current_path != NULL) {
        for (i = 0; i < s->top; i++) {
            str_len++;
            current_path = (char *) realloc(current_path, (str_len * sizeof(s->elems[i])) + 1);
            strcat(current_path, s->elems[i]);
            strcat(current_path, "/");
        }
    }

    return current_path;
}

int main() {
    char *strings[] = {
        ".",
        "test_dir",
        "test_dir_2",
        "test_dir_3"
    };
    char *current_path;
    s = stack_new();
    int i = 0;

    for (i = 0; i < SIZEOF(strings); i++) {
        stack_push(s, strings[i]);
    }

    current_path = get_dir_path(s);
    printf("%s\n", current_path);

    free(current_path);
    empty_stack(s);
    return 0;
}
