#ifndef OPTIONS_H
#define OPTIONS_H

#define ST_RECURSIVE 0
#define ST_REGULAR 1
#define ST_SINGLE_FILE 2

#include "lists/linked_list.h"

unsigned char search_type;
char *haystack;
char *needle;

extern void init_option();
extern void parse_general_flags(char *flags);
extern linked_list *parse_ignore_flags(char *ignore_str);
extern void grepple_help();
#endif
