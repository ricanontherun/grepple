#ifndef OPTIONS_H
#define OPTIONS_H

#include "lists/linked_list.h"
#include "stack/stack.h"

//typedef struct {
//    char *haystack;
//    char *needle;
//    unsigned int search_type;
//    linked_list *ext_ignore_list;
//    stack *current_directory_stack;
//} grepple_grepple;

char *haystack;
char *needle;

extern void parse_general_flags(char *flags);
extern void parse_ignore_flags(char *ignore_str);

#endif
