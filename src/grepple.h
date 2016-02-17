#ifndef GREPPLE_H
#define GREPPLE_H

#include <regex.h>
#include <stdint.h>

#include "lists/linked_list.h"
#include "stack/stack.h"

typedef enum traversal_flags {
    TRAVERSAL_REGULAR = 1,
    TRAVERSAL_RECURSIVE = 2,
    TRAVERSAL_FILE = 4
} traversal_flags;

typedef enum search_flags {
    SEARCH_TERM,
    SEARCH_PATTERN
} search_flags;

// ENUM?
#define FLAG_PREFIX "-"
#define FLAG_RECURSIVE 'r'
#define FLAG_PATTERN 'p'
#define FLAG_HELP "--help"

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
    uint32_t s_flags;
    uint32_t  t_flags;

    // Structures used when executing regular expressions.
    regex_t *pattern;

    // TODO: Get rid of these.
    linked_list *ext_ignore_list;
    stack *current_directory_stack;

    search search_list;
} greppleData;

void greppleInit(greppleData *grepple);
void greppleStart(greppleData *grepple);
void greppleDestroy(greppleData *grepple);
void greppleSetup(greppleData *grepple);

#endif //GREPPLE_GREPPLE_H
