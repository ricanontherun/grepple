#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../deps/linux/list.h"
#include "grepple.h"
#include "mem.h"
#include "search.h"
#include "match_printer.h"

static void _initSearch(search *context) {
    context->result_count = 0;

    // Initialize the list of results.
    INIT_LIST_HEAD(&(context->results.list));
}

/**
 *  Search a file for a keyword.
 *  
 *  @param file_path (uint8_t *) Full file path
 *  @param search_term (uint8_t *) Keyword to search for
 */
void searchFile(greppleData *grepple, uint8_t *file_path, uint8_t *search_term) {
    FILE *fp = getFile(file_path, "r");
    uint8_t read_block[READ_BLOCK_SIZE];
    uint16_t line_count = 0;

    if ( fp != NULL ) {
        result *hit;
        search *context = NEW(search);
        context->filename = strdup(file_path);
        _initSearch(context);

        while ( fgets(read_block, READ_BLOCK_SIZE, fp) != NULL ) {
            // We've passed a new line.
            if ( strchr(read_block, '\n') != NULL ) {
                line_count++;
            }

            if ( strstr(read_block, search_term) != NULL ) {
                context->result_count++;

                // Create a new result object.
                hit = NEW(result);
                hit->context = strdup(read_block);
                hit->line_number = line_count;

                // Add the result to the results list.
                // Each result has a list_head, so we pass that to list_add along with the main list address.
                list_add(&(hit->list), &(context->results.list));
            }

        }

        fclose(fp);

        if ( context->result_count > 0 ) {
            // Add this context to the list.
            list_add(&(context->list), &(grepple->search_list.list));
        } else {
            free(context->filename);
            free(context);
        }

        return;
    }
}
