#include <stdio.h>
#include "init.h"
#include "fs_parser.h"
#include "options.h"

void grepple_init() {
    open_resources();
    switch (search_type) {
        case ST_RECURSIVE:
            recursive_search("git", "int");
            break;
    }
    close_resources();
}
