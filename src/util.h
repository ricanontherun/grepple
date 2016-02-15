#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#include "lists/linked_list.h"

#define LTRIM(s) \
            do { \
                while ( isspace(*s) ) { s++; }; \
            } while(0)

#define RTRIM(s) \
            do { \
                char *end = s + strlen(s)- 1; \
                while ( end > s && isspace(*end) ) { end--; } \
            } while (0)

char *trim(char *s);

#endif
