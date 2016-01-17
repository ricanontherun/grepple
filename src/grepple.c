#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../deps/linux/list.h"
#include "grepple.h"
#include "search.h"
#include "dir.h"

/**
 * Initialize grepple data structures.
 */
void greppleInit(greppleData *grepple) {
    grepple->ext_ignore_list = ll_new();
    grepple->current_directory_stack = stack_new();

    grepple->search_type = SEARCH_TYPE_REGULAR;

    INIT_LIST_HEAD(&(grepple->search_list.list));
}

void greppleDestroy(greppleData *grepple) {
    if ( grepple->ext_ignore_list != NULL ) {
        ll_free_list(grepple->ext_ignore_list);
        grepple->ext_ignore_list = NULL;
    }

    if ( grepple->current_directory_stack != NULL ) {
        empty_stack(grepple->current_directory_stack);
        grepple->current_directory_stack = NULL;
    }

    // Free up any result and context lists.
    // Now we can loop through them and display the hit and clean up the list.
    search *search_tmp;
    struct list_head *search_pos, *search_q;
    list_for_each_safe(search_pos, search_q, &(grepple->search_list.list) ) {
        search_tmp = list_entry(search_pos, search, list);

        // Free all search results in this search context.
        result *tmp;
        struct list_head *pos, *q;
        list_for_each_safe(pos, q, &(search_tmp->results.list) ) {
            tmp = list_entry(pos, result, list);

            list_del(pos);

            free(tmp->context);
            free(tmp);
        }

        list_del(search_pos);

        free(search_tmp->filename);
        free(search_tmp);
    }
}
/**
 * Start the main directory traversal routines.
 */
void greppleStart(greppleData *grepple) {
    switch( getFileType(grepple->haystack) ) {
        case S_IFREG: // Regular file
            if ( grepple->search_type == SEARCH_TYPE_RECURSIVE ) {
                printf("Recursive flag provided with non-directory haystack, ignoring...\n");
            }

            searchFile(grepple, grepple->haystack, grepple->needle);
            break;
        case S_IFDIR: // Directory
            searchDirectory(grepple->haystack, grepple->needle);
            break;
    }

    displayResults();
    return;
}
