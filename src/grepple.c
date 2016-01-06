#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "grepple.h"
#include "search.h"

// Global grepple object.
greppleData grepple;

/**
 *  Display grepple help.
 */
void displayHelp() {
    printf(        "   ___                   _     \n"
                   "  / __|_ _ ___ _ __ _ __| |___ \n"
                   " | (_ | '_/ -_) '_ \\ '_ \\ / -_)\n"
                   "  \\___|_| \\___| .__/ .__/_\\___|\n"
                   "              |_|  |_|         \n\n"
                    "Usage: grepple [OPTS] HAYSTACK NEEDLE\n"
                   "Search a file or directory for a keyword\n"
                   "  -r\t\t\tRecursive, ignored if a non-directory HAYSTACK argument is provided\n"
                           "  -e\t\t\tDisplay examples\n"
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

/**************************************************
|
| Grepple object management
|
***************************************************/
/**
 * Initialize grepple data structures.
 */
void initGrepple() {
    grepple.ext_ignore_list = ll_new();
    grepple.current_directory_stack = stack_new();

    grepple.search_type = SEARCH_TYPE_REGULAR;
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

/***************************************************
|
| Option Parsing
|
****************************************************/
void parseGeneralFlags(char *flags) {
    unsigned int i;
    for ( i = 1; i < strlen(flags); i++ ) {
        printf("%d\n", flags[i]);
        switch ( flags[i] ) {
            case FLAG_RECURSIVE:
                grepple.search_type = SEARCH_TYPE_RECURSIVE;
                break;
            default:
                grepple.search_type = SEARCH_TYPE_REGULAR;
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
    // First, check for the help flag.
    if ( strcmp(argv[0], FLAG_HELP) == 0 || strcmp(argv[0], FLAG_HELP_SHORT) == 0 ) {
        printf("Displaying the help by request\n");
        displayHelp();
    }

    grepple.haystack = argv[argc - 2];
    grepple.needle = argv[argc - 1];

    unsigned int i = 0;

    for ( i = 0; i < argc; i++ ) {
        if ( strstr(argv[i], "-izgnore") ) {
            printf("Parsing ignore flags\n");
//            parse_ignore_flags(argv[i]);
        } else if ( strstr(argv[i], FLAG_PREFIX) || strstr(argv[i], FLAG_PREFIX_SHORT) ) {
            printf("Parsing general flags\n");
            parseGeneralFlags(argv[i]);
        }
    }

}

/**
 * Start the main directory traversal routines.
 */
void startGrepple() {
    switch( getFileType(grepple.haystack) ) {
        case S_IFREG: // Regular file
            if ( grepple.search_type == SEARCH_TYPE_RECURSIVE ) {
                printf("Recursive flag provided with non-directory haystack, ignoring...\n");
            }

            searchFile(grepple.haystack, grepple.needle);
            break;
        case S_IFDIR: // Directory
            printf("Beginning directory traversal\n");
//            dir_search(grepple.haystack, grepple.needle);
            break;
    }

    return;
}

int main(int argc, char **argv) {
    if ( argc < 2 ) {
        displayHelp();
        exit(EXIT_FAILURE);
    }

    initGrepple();

    parseFlags(argc, argv);

    startGrepple();

    destroyGrepple();

    exit(EXIT_SUCCESS);
}
