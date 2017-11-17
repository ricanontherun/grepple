#include <stdlib.h>
#include <sys/stat.h>

#include "../deps/linux/list.h"
#include "grepple.h"
#include "search.h"
#include "dir.h"

/**
 * Initialize grepple data structures and default values.
 */
void greppleInit(greppleData *grepple) {
    grepple->current_directory_stack = stack_new(100);

    // Set some default values.
    grepple->s_flags = SEARCH_TERM;
    grepple->pattern = NULL;

    // Set flags which depend on the haystack provided.
    switch( getFileType(grepple->haystack) ) {
        case S_IFREG: // Regular file
            grepple->t_flags |= TRAVERSAL_FILE;
            break;
        case S_IFDIR: // Directory
            grepple->t_flags |= TRAVERSAL_REGULAR;
            break;
    }

    // Initialize the search list.
    INIT_LIST_HEAD(&(grepple->search_list.list));
}

void greppleFree(greppleData *grepple) {
    if ( grepple->current_directory_stack != NULL ) {
        empty_stack(grepple->current_directory_stack);
        grepple->current_directory_stack = NULL;
    }

    if ( grepple->pattern != NULL ) {
        regfree(grepple->pattern);
        free(grepple->pattern);
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

    if ( grepple->t_flags & TRAVERSAL_FILE ) {
        searchFile(grepple, grepple->haystack, grepple->needle);
    } else if ( grepple->t_flags & ( TRAVERSAL_REGULAR | TRAVERSAL_RECURSIVE ) ) {
        searchDirectory(grepple, grepple->haystack, grepple->needle);
    }

    return;
}
