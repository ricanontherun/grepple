#ifndef GREPPLE_H
#define GREPPLE_H

#include <stdint.h>

#include "search.h"
#include "lists/linked_list.h"
#include "stack/stack.h"

#define SEARCH_TYPE_RECURSIVE 0
#define SEARCH_TYPE_REGULAR 1
#define SEARCH_TYPE_SINGLE_FILE 2

#define FLAG_PREFIX "--"
#define FLAG_PREFIX_SHORT "-"
#define FLAG_RECURSIVE 'r'
#define FLAG_HELP "-help"
#define FLAG_HELP_SHORT "-h"
#define FLAG_IGNORE "--"

typedef struct {
    // Search options
    uint8_t *haystack;
    uint8_t *needle;
    uint8_t search_type;

    // TODO: Get rid of these.
    linked_list *ext_ignore_list;
    stack *current_directory_stack;

    search search_list;
} greppleData;

void greppleInit(greppleData *grepple);
void greppleStart(greppleData *grepple);
void greppleDestroy(greppleData *grepple);

#endif //GREPPLE_GREPPLE_H
