#include <stdlib.h>

#include "init.h"
#include "options.h"
#include "fs_parser.h"
#include "lists/linked_list.h"
#include "stack/stack.h"

extern grepple_search_options *search_options;

void grepple_free_resources() {
    if (search_options->ext_ignore_list != NULL) {
        ll_free_list(search_options->ext_ignore_list);
        search_options->ext_ignore_list = NULL;
    }

    if (search_options->current_directory_stack != NULL) {
       empty_stack(search_options->current_directory_stack);
       search_options->current_directory_stack = NULL;
    }

    if (search_options != NULL) {
        free(search_options);
        search_options = NULL;
    }
}

void grepple_init_resources() {
    search_options = malloc(sizeof(grepple_search_options));
    search_options->search_type = ST_REGULAR;
    search_options->current_directory_stack = stack_new();
    search_options->ext_ignore_list = ll_new(); 
}

void grepple_exit(unsigned int exit_status) {
    grepple_free_resources();

    switch (exit_status) {
        case 0:
            exit(EXIT_SUCCESS);
            break;
        case 1:
            exit(EXIT_FAILURE);
            break;
    }
}

void grepple_init() {
    dir_search(search_options->haystack, search_options->needle);
    return;
}
