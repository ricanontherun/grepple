#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../deps/linux/list.h"
#include "grepple.h"
#include "file.h"

#define READ_BLOCK_SIZE 100

/**
 * A result represents a search "hit" with members including the line number
 * and a some surrounding text for context.
 */
typedef struct result {
    uint16_t line_number;
    uint8_t *context;
    struct list_head list;
} result;

/**
 * A search represents a file with a list of results and a result_count.
 */
typedef struct search {
    uint8_t *filename;
    uint16_t result_count;
    result results;
    struct list_head list;
} search;

void searchFile(greppleData *grepple, uint8_t *file_path, uint8_t *search_term);

#endif
