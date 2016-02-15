#include "util.h"

char *trim(char *s) {
    LTRIM(s);
    RTRIM(s);
    return s;
}
