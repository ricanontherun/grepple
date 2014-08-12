/*
    Make sure the ignore flags parser works.
*/
#include <stdio.h>
#include <string.h>
#include "../src/lists/linked_list.h"
#include "../src/options.h"
#include "../src/init.h"

unsigned int is_valid(char *s) {
    unsigned int valid = 1;
    char *ext = strchr(s, '.');

    if (ext != NULL) {     
        valid = !ll_node_exists(search_options->ext_ignore_list, ext);
    }
    return valid;
}
int main(int argc, char *argv[]) {
    unsigned int i;
    grepple_init_resources();
    for (i = 0; i < argc; i++) {
        if (strstr(argv[i], "--ignore")) {
            parse_ignore_flags(argv[i]);
            printf("%d\n", is_valid("main.c.fuck"));
        }
    }
    grepple_free_resources();
    return 1;
}
