#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../deps/linux/list.h"
#include "mem.h"
#include "grepple.h"
#include "search.h"
#include "match_printer.h"

// Remember, we are simply declaring the existence of grepple here.
extern greppleData grepple;

/**
 *  Search a file for a keyword.
 *  
 *  @param file_path (char *) Full file path
 *  @param search_term (char *) Keyword to search for
 */
void searchFile(char *file_path, char *search_term) {
    FILE *fp = getFile(file_path, "r");
    char read_block[READ_BLOCK_SIZE];
    int line_count = 0;

    if ( fp != NULL ) {
        search_result *result;
        search_context context;
        context.filename = file_path;
        initSearchContext(&context);

        while ( fgets(read_block, READ_BLOCK_SIZE, fp) != NULL ) {
            // We've passed a new line.
            if ( strchr(read_block, '\n') != NULL ) {
                line_count++;
            }

            if ( strstr(read_block, search_term) != NULL ) {
                context.result_count++;

                // Allocate memory for the new result.
                result = NEW(search_result);
                result->context = strdup(read_block);
                result->line_number = line_count;

                // Add the result to the results list.
                // Each result has a list_head, so we pass that to list_add along with the main list address.
                list_add(&(result->list), &(context.results.list));
            }

        }

        fclose(fp);

        printf("%s\n", context.filename);
        // Now we can loop through them and display the result and clean up the list.
        search_result *tmp;
        struct list_head *pos, *q;
        list_for_each_safe(pos, q, &(context.results.list) ) {
            tmp = list_entry(pos, search_result, list);

            report_match(stdout, context.filename, tmp->line_number, tmp->context);
            list_del(pos);

            free(tmp->context);
            free(tmp);
        }
    }
}

void initSearchContext(search_context *context) {
    context->result_count = 0;

    // Initialize the list of results.
    INIT_LIST_HEAD(&(context->results.list));
}
