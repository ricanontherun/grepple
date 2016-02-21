#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <regex.h>

#include "../deps/linux/list.h"
#include "output.h"
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
    FILE *fp = fopen(file_path, "r");

    if ( fp == NULL ) {
        greppleError("Failed to open file\n");
        return;
    }

    uint8_t read_block[READ_BLOCK_SIZE];
    uint16_t line_count = 0;

    if ( fp != NULL ) {
        result *_result;
        search *context = NEW(search);
        context->filename = strdup(file_path);
        _initSearch(context);

        while ( fgets(read_block, READ_BLOCK_SIZE, fp) != NULL ) {
            if ( strchr(read_block, '\n') != NULL ) {
                line_count++;
            }

            bool hit = 0;

            // Depending on the provided flags, we either perform
            // a basic strstr match or execute the compiled regular expression.
            if ( grepple->s_flags == SEARCH_TERM ) {
                hit = strstr(read_block, search_term) != NULL;
            } else {
                int reti;
                reti = regexec(grepple->pattern, read_block, 0, NULL, 0);
                hit = !reti;
            }

            // We have a hit, attach it to this file's result list.
            if ( hit == true ) {
                context->result_count++;

                char *trimmed_context = trim(read_block);

                _result = NEW(result);
                _result->context = strdup(trimmed_context);
                _result->line_number = line_count;

                list_add(&(_result->list), &(context->results.list));
            }
        }

        fclose(fp);

        // We're only going to add this result to the list
        // if the search found at least one hit.
        if ( context->result_count > 0 ) {
            list_add(&(context->list), &(grepple->search_list.list));
        } else { // Free up the space otherwise.
            free(context->filename);
            free(context);
        }

        return;
    }
}
