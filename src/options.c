#include <stdio.h>
#include <string.h>
#include "options.h"

extern unsigned char search_type;

void init_options() {
    search_type = ST_REGULAR;
}
void parse_general_flags(char *flags) {
    int i;
    for (i = 1; i < strlen(flags); i++) {
        switch (flags[i]) {
            case 'r':
                search_type = ST_RECURSIVE;
                break;
            default:
                break;
        }
    }
}

void parse_ignore_flags(char *ignore_str) {

}
