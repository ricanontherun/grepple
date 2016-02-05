#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../deps/linux/list.h"
#include "grepple.h"
#include "mem.h"
#include "search.h"
#include "util.h"

static void _initSearch(search *context) {
    context->result_count = 0;

    // Initialize the list of results.
    INIT_LIST_HEAD(&(context->results.list));
}

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

                char *trimmed_context = trim(read_block);

                hit = NEW(result);
                hit->context = strdup(trimmed_context);
                hit->line_number = line_count;

                list_add(&(hit->list), &(context->results.list));
            }
        }

        fclose(fp);

        // We're only going to add this result to the results list
        // if the search found at least one hit. Obviously.
        if ( context->result_count > 0 ) {
            list_add(&(context->list), &(grepple->search_list.list));
        } else { // Free up the space otherwise.
            free(context->filename);
            free(context);
        }

        return;
    }
}
