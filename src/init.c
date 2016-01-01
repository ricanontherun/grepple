/**
 *  File: init.c
 *  Functions which handle the initialization and cleanup of runtime memory/strucutres
 */
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#include "mem.h"
#include "filer.h"
#include "grepple.h"
#include "init.h"
#include "options.h"
#include "fs_parser.h"
#include "searcher.h"

extern greppleData *grepple;

void grepple_free_resources() {
    if (grepple != NULL) {
        if (grepple->ext_ignore_list != NULL) {
            ll_free_list(grepple->ext_ignore_list);
            grepple->ext_ignore_list = NULL;
        }

        if (grepple->current_directory_stack != NULL) {
           empty_stack(grepple->current_directory_stack);
           grepple->current_directory_stack = NULL;
        }

        if (grepple != NULL) {
            free(grepple);
            grepple = NULL;
        }
    }
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
    switch(stat_file_type(grepple->haystack)) {
        case S_IFREG: // Regular file
            if (grepple->search_type == ST_RECURSIVE) {
                printf("grepple: Recursive flag provided with non-directory haystack, ignoring...\n");
            }
            search_for_term(grepple->haystack, grepple->needle);
            break;
        case S_IFDIR: // Directory
            dir_search(grepple->haystack, grepple->needle);
            break;
    }

    return;
}
