#ifndef GREPPLE_H
#define GREPPLE_H

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

typedef struct {
    // Search options
    char *haystack;
    char *needle;
    unsigned int search_type;
    linked_list *ext_ignore_list;
    stack *current_directory_stack;

    // Other data structures....
    search search_list;
} greppleData;

#endif //GREPPLE_GREPPLE_H
