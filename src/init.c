#include <stdio.h>
#include "init.h"
#include "fs_parser.h"
#include "options.h"

void grepple_init() {
    open_resources();
    dir_search(haystack, needle);
    close_resources();
}
