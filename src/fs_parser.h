#ifndef FS_PARSER
#define FS_PARSER

#include "stack.h"
extern void start_dir_loop();
extern void print_dir_contents(char *dirname, char *search_term);
extern void get_dir_path(stack *s);
#endif
