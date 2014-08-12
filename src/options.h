#ifndef OPTIONS_H
#define OPTIONS_H

#define ST_RECURSIVE 0
#define ST_REGULAR 1
#define ST_SINGLE_FILE 2

#include "lists/linked_list.h"
#include "stack/stack.h"

typedef struct {
    char *haystack;
    char *needle;
    unsigned int search_type;
    linked_list *ext_ignore_list;
    stack *current_directory_stack;
} grepple_search_options;

grepple_search_options *search_options;

char *haystack;
char *needle;

extern void parse_general_flags(char *flags);
extern void parse_ignore_flags(char *ignore_str);
extern void grepple_help();
#endif
