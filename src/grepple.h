#ifndef GREPPLE_H
#define GREPPLE_H

#include <stdint.h>

#include "lists/linked_list.h"
#include "stack/stack.h"

typedef enum search_type {
    SEARCH_TYPE_RECURSIVE,
    SEARCH_TYPE_REGULAR,
    SEARCH_TYPE_SINGLE_FILE
} search_type;

// ENUM?
#define FLAG_PREFIX "--"
#define FLAG_PREFIX_SHORT "-"
#define FLAG_RECURSIVE 'r'
#define FLAG_HELP "-help"
#define FLAG_HELP_SHORT "-h"
#define FLAG_IGNORE "--"

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

typedef struct {
    // Search options
    uint8_t *haystack;
    uint8_t *needle;
    search_type type;

    // TODO: Get rid of these.
    linked_list *ext_ignore_list;
    stack *current_directory_stack;

    search search_list;
} greppleData;

void greppleInit(greppleData *grepple);
void greppleStart(greppleData *grepple);
void greppleDestroy(greppleData *grepple);

#endif //GREPPLE_GREPPLE_H
