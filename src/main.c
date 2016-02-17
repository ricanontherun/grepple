#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../deps/linux/list.h"
#include "mem.h"
#include "output.h"
#include "grepple.h"

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
                           "Usage: grepple [FLAGS] HAYSTACK NEEDLE\n"
                           "Search a file or directory for a keyword\n"
                           "  r\t\t\tRecursive, ignored if a non-directory HAYSTACK argument is provided\n"
                           "  p\t\t\tTreat NEEDLE as a POSIX regular expression\n"
                           "  --ignore[...]\t\tExtension ignore, comma seperated list of file extensions to be ignored\n"
                           "  --help\t\tDisplay this help text\n"
                           "  HAYSTACK\t\tFile or directory to search for NEEDLE\n"
                           "  NEEDLE\t\tTerm or pattern\n"
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

        if ( !(grepple->t_flags & TRAVERSAL_FILE) ) {
            printf("\n----------------------------------\n");
            printf("| %s\n", search_entry->filename);
            printf("----------------------------------\n");
        }

        result *result_entry;
        struct list_head *result_pos, *result_tmp;
        list_for_each_safe( result_pos, result_tmp, &(search_entry->results.list) ) {
            result_entry = list_entry(result_pos, result, list);

            printf("%d:\t%s" "\x1b[0m", result_entry->line_number, result_entry->context);
        }
    }
}

/**
 * Attempt to compile a POSIX regular expression.
 *
 * uint32_t* pattern
 */
void compilePattern(uint8_t *pattern) {
    regex_t *regex = NEW(regex_t);
    int32_t reti;

    reti = regcomp(regex, pattern, 0);

    // Something went wrong in the compilation process.
    if ( reti ) {
        printf("Please provide a valid POSIX regular expression\n");
        greppleDestroy(&grepple);
        exit(1);
    }

    grepple.pattern = regex;
}


/***************************************************
|
| Option Parsing
|
****************************************************/
void parseGeneralFlags(uint8_t *flags) {
    uint8_t i;
    size_t flag_len = strlen(flags);

    for ( i = 1; i < flag_len; i++ ) {
        switch ( flags[i] ) {
            case FLAG_RECURSIVE:
                grepple.t_flags |= TRAVERSAL_RECURSIVE;
                break;
            case FLAG_PATTERN:
                compilePattern(grepple.needle);
                grepple.s_flags = SEARCH_PATTERN;
                break;
        }
    }
}

void parseFlags(int argc, uint8_t **argv) {
    // The starting file and search term are always the last
    // and second to last arguments, respectively.
    grepple.haystack = argv[argc - 2];
    grepple.needle = argv[argc - 1];

    uint8_t i = 0;

    for ( i = 0; i < argc; i++ ) {
        // Check for help.
        if ( strcmp(argv[i], FLAG_HELP) == 0 ) {
            displayHelp();
            greppleDestroy(&grepple);
            exit(0);
        }

        if ( strstr(argv[i], "-ignore") ) {
            printf("woah there\n");

        } else if ( strstr(argv[i], FLAG_PREFIX) ) {
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

    greppleSetup(&grepple);

    greppleStart(&grepple);

    displayResults(&grepple);

    greppleDestroy(&grepple);

    exit(EXIT_SUCCESS);
}

