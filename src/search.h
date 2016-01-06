#ifndef SEARCHER_H
#define SEARCHER_H

#include <string.h>
#include <stdlib.h>

#include "../deps/linux/list.h"
#include "file.h"

#define READ_BLOCK_SIZE 100

typedef struct search_result {
    unsigned int line_number;
    char *context;
    struct list_head list;
} search_result;

typedef struct search_context {
    char *filename;
    unsigned int result_count;
    search_result results;
} search_context;

void initSearchContext(search_context *context);
void searchFile(char *file_path, char *search_term);

#endif
