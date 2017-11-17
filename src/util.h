#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x[0])))

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

char * StringJoin(char ** strings, size_t length, char * delim);

#endif
