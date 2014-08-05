/*
    Linked list test.
    Read bytes from a file into the linked list.
*/
#include <stdio.h>
#include <string.h>
#include "../src/filer.h"
#include "../src/lists/linked_list.h"

void parse_ignore_flags(char *s) {
    
}

int main(int argc, char *argv[]) {
    linked_list *ll = ll_new();
    int i;

    for (i = 0; i < argc; i++) {
        if (strstr(argv[i], "--ignore")) {
            parse_ignore_flags(argv[i]);
        }
    }
    ll_free_list(ll);
    return 1;
}
