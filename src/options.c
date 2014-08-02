#include <stdio.h>
#include <string.h>
#include "options.h"

extern unsigned char search_type;
extern char *haystack;
extern char *needle;

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
    return;
}

void grepple_help() {
    printf("Usage: grepple [OPTS] HAYSTACK NEEDLE\n"
            "Search a file or directory for a keyword\n"
            "  -r\t\t\tRecursive, ignored if a non-directory HAYSTACK argument is provided\n"
            "  --ignore[...]\t\tExtension ignore, comma seperated list of file extensions to be ignored\n"
            "  --help\t\tDisplay this help text\n"
            "  HAYSTACK\t\tFile or directory to search for NEEDLE\n"
            "  NEEDLE\t\tKeyword to be located\n"
            "\nExamples:\n"
            "  grepple -r git int\n"
            "\tRecursively search the git directory for int\n"
            "\n"
    );

    return;
}
