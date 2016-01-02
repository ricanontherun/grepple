#ifndef GREPPLE_H
#define GREPPLE_H

#include "lists/linked_list.h"
#include "stack/stack.h"

#define SEARCH_TYPE_RECURSIVE 0
#define SEARCH_TYPE_REGULAR 1
#define SEARCH_TYPE_SINGLE_FILE 2

typedef struct {
    // Search options
    char *haystack;
    char *needle;
    unsigned int search_type;
    linked_list *ext_ignore_list;
    stack *current_directory_stack;

    // Other data structures....
} greppleData;

#endif //GREPPLE_GREPPLE_H
