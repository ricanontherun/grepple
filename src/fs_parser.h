#ifndef FS_PARSER
#define FS_PARSER

#include "stack/stack.h"

extern char *get_dir_path(stack *s);
extern void dir_search(char *dirname, char *search_term);
extern unsigned int is_valid_directory(char *dir_name);

#endif
