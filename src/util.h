#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#include "lists/linked_list.h"

void string_split_to_ll(char *s, linked_list *list, char delim);
char *trim(char *s);

#endif
