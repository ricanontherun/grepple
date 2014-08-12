#include <stdio.h>
#include <string.h>

#include "options.h"
#include "lists/linked_list.h"
#include "util.h"

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

linked_list *parse_ignore_flags(char *s) {
    unsigned short i;
    unsigned char *lbp = strchr(s, '[');
    unsigned char *rbp = strchr(s, ']');
    unsigned char *p;
    size_t len = strlen(s);
    unsigned char ig_opts[len];

    if (lbp && rbp && (lbp < rbp)) {
        p = ++lbp;
        i = 0;

        while (*p != ']') {
            ig_opts[i++] = *p;
            p++;
        }

        ig_opts[i] = '\0';
        linked_list *ig_list = ll_new();
        string_split_to_ll(ig_opts, ig_list, ',');
        return ig_list;
    } else {
        printf("Displaying grepple help...\n");
        return NULL;
    }
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
