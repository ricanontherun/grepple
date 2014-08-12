/*
 *     Linked list test.
 *         Read bytes from a file into the linked list.
 *         */
#include <stdio.h>
#include <string.h>
#include "../src/options.h"
#include <stdlib.h>

typedef struct {
    linked_list *ig_list;
} glob;

glob *glob_s;

void grepple_free_resources() {
    if (glob_s->ig_list != NULL)
        ll_free_list(glob_s->ig_list);

    if (glob_s != NULL) {
        free(glob_s);
    }
}

int main(int argc, char *argv[]) {
    unsigned int i;
    glob_s = malloc(sizeof(glob));

    for (i = 0; i < argc; i++) {
        if (strstr(argv[i], "--ignore")) {
            glob_s->ig_list = parse_ignore_flags(argv[i]);
            if (glob_s->ig_list != NULL) {
                ll_print_list(glob_s->ig_list);
                int k = ll_node_exists(glob_s->ig_list, ".h");
                printf("%d\n", k);
            }
        }
    }
    grepple_free_resources();
    return 1;
}
