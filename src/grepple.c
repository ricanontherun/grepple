#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "grepple.h"

// Global grepple object.
greppleData grepple;

/**
 *  Display grepple help.
 */
void display_help() {
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

/**
 * Initialize grepple data structures.
 */
void initGrepple() {
    grepple.ext_ignore_list = ll_new();
    grepple.current_directory_stack = stack_new();
}

void destroyGrepple() {
    if ( grepple.ext_ignore_list != NULL ) {
        ll_free_list(grepple.ext_ignore_list);
        grepple.ext_ignore_list = NULL;
    }

    if ( grepple.current_directory_stack != NULL ) {
        empty_stack(grepple.current_directory_stack);
        grepple.current_directory_stack = NULL;
    }
}

/**************************************************
|
| Option Parsing
|
****************************************************/
void parseGeneralFlags(char *flags) {
    unsigned int i;
    for ( i = 1; i < strlen(flags); i++ ) {
        switch (flags[i]) {
            case 'r':
                grepple.search_type = SEARCH_TYPE_RECURSIVE;
                break;
            default:
                break;
        }
    }
}

void parseIgnoreFlags(char *s) {
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
//        string_split_to_ll(ig_opts, grepple.ext_ignore_list, ',');
    } else {
        exit(EXIT_FAILURE);
    }
}

void parseFlags(int argc, char **argv) {
    grepple.haystack = argv[argc - 2];
    grepple.needle = argv[argc - 1];

    unsigned int i = 0;

    for ( i = 0; i < argc; i++ ) {
        if ( argv[i][0] == '-' && argv[i][1] != '-' ) {
            parseGeneralFlags(argv[i]);
        } else if ( strstr(argv[i], "--ignore") ) {
//            parse_ignore_flags(argv[i]);
        } else if ( strstr(argv[i], "--help") ) {
            display_help();
//            grepple_exit(0);
        }
    }

}

/**
 * Start the main directory traversal routines.
 */
void startGrepple() {
//    switch(stat_file_type(grepple.haystack)) {
//        case S_IFREG: // Regular file
//            if (grepple.search_type == ST_RECURSIVE) {
//                printf("grepple: Recursive flag provided with non-directory haystack, ignoring...\n");
//            }
//            search_for_term(grepple.haystack, grepple.needle);
//            break;
//        case S_IFDIR: // Directory
//            dir_search(grepple.haystack, grepple.needle);
//            break;
//    }
//
//    return;
}

int main(int argc, char **argv) {
    // Honestly, we should do ALL option/flag checking here.
    if (argc < 3) {
        display_help();
        exit(1);
    }

    initGrepple();

    parseFlags(argc, argv);

    startGrepple();

    destroyGrepple();
//
//    grepple_init();
//    grepple_exit(0);
}
