#ifndef SEARCHER_H
#define SEARCHER_H

#include <string.h>
#include <stdlib.h>

#include "../deps/linux/list.h"
#include "file.h"

#define READ_BLOCK_SIZE 100

/**
 * A result represents a search "hit" with members including the line number
 * and a some surrounding text for context.
 */
typedef struct result {
    unsigned int line_number;
    char *context;

    struct list_head list;
} result;

/**
 * A search represents a file with a list of results and a result_count.
 */
typedef struct search {
    char *filename;
    unsigned int result_count;
    result results;

    struct list_head list;
} search;

void searchFile(char *file_path, char *search_term);

#endif
