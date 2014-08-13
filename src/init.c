/**
 *  File: init.c
 *  Functions which handle the initialization and cleanup of runtime memory/strucutres
 */
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include "filer.h"
#include "init.h"
#include "options.h"
#include "fs_parser.h"
#include "lists/linked_list.h"
#include "stack/stack.h"
#include "searcher.h"

extern grepple_search_options *search_options;

void grepple_free_resources() {
    if (search_options != NULL) {
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
}

void grepple_init_resources() {
    search_options = malloc(sizeof(grepple_search_options));
    search_options->search_type = ST_REGULAR;
    search_options->current_directory_stack = stack_new();
    search_options->ext_ignore_list = ll_new(); 
}

/**
 *  Free grepple resources and exit
 *
 *  @param exit_status (unsigned int) Desired exit status
 */
void grepple_exit(unsigned int exit_status) {
    grepple_free_resources();

    switch (exit_status) {
        case 0:
            exit(EXIT_SUCCESS);
            break;
        case 1:
            exit(EXIT_FAILURE);
            break;
        default:
            exit(EXIT_FAILURE);
            break;
    }
}

void grepple_init() {
    switch(stat_file_type(search_options->haystack)) {
        case S_IFREG: // Regular file
            if (search_options->search_type == ST_RECURSIVE) {
                printf("grepple: Recursive flag provided with non-directory haystack, ignoring...\n");
            }
            search_for_term(search_options->haystack, search_options->needle);
            break;
        case S_IFDIR: // Directory
            dir_search(search_options->haystack, search_options->needle);
            break;
    }

    return;
}
