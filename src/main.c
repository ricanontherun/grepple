#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../deps/linux/list.h"
#include "grepple.h"
#include "search.h"
#include "dir.h"

// grepple object declaration
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

void displayResults(greppleData *grepple) {
    search *search_entry;
    struct list_head *search_pos, *search_tmp;
    list_for_each_safe( search_pos, search_tmp, &(grepple->search_list.list) ) {
        search_entry = list_entry(search_pos, search, list);

        printf("%s\n", search_entry->filename);

        result *result_entry;
        struct list_head *result_pos, *result_tmp;
        list_for_each_safe( result_pos, result_tmp, &(search_entry->results.list) ) {
            result_entry = list_entry(result_pos, result, list);

            printf("%d:\t%s", result_entry->line_number, result_entry->context);
        }
    }
}
/***************************************************
|
| Option Parsing
|
****************************************************/
void parseGeneralFlags(uint8_t *flags) {
    uint8_t i;
    for ( i = 1; i < strlen(flags); i++ ) {
        printf("%d\n", flags[i]);
        switch ( flags[i] ) {
            case FLAG_RECURSIVE:
                grepple.type = SEARCH_TYPE_RECURSIVE;
                break;
            default:
                grepple.type = SEARCH_TYPE_REGULAR;
                break;
        }
    }
}

void parseIgnoreFlags(uint8_t *s) {
    uint16_t i;
    uint8_t *lbp = strchr(s, '[');
    uint8_t *rbp = strchr(s, ']');
    uint8_t *p;

    size_t len = strlen(s);
    uint8_t ig_opts[len];

    if (lbp && rbp && (lbp < rbp)) {
        p = ++lbp;
        i = 0;

        while (*p != ']') {
            ig_opts[i++] = *p;
            p++;
        }

        ig_opts[i] = '\0';
        // We really don't need a linked list.
        // A simple string comparison could do.
//        string_split_to_ll(ig_opts, grepple.ext_ignore_list, ',');
    } else {
        exit(EXIT_FAILURE);
    }
}

void parseFlags(int argc, uint8_t **argv) {
    // First, check for the help flag.
    if ( strcmp(argv[0], FLAG_HELP) == 0 || strcmp(argv[0], FLAG_HELP_SHORT) == 0 ) {
        printf("Displaying the help by request\n");
        displayHelp();
    }

    grepple.haystack = argv[argc - 2];
    grepple.needle = argv[argc - 1];

    uint8_t i = 0;

    for ( i = 0; i < argc; i++ ) {
        if ( strstr(argv[i], "-ignore") ) {
//            parse_ignore_flags(argv[i]);
        } else if ( strstr(argv[i], FLAG_PREFIX) || strstr(argv[i], FLAG_PREFIX_SHORT) ) {
            parseGeneralFlags(argv[i]);
        }
    }
}

int main(int argc, uint8_t **argv) {
    if ( argc < 2 ) {
        displayHelp();
        exit(EXIT_FAILURE);
    }

    greppleInit(&grepple);

    parseFlags(argc, argv);

    greppleStart(&grepple);

    displayResults(&grepple);

    greppleDestroy(&grepple);

    exit(EXIT_SUCCESS);
}

