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

        printf("\n----------------------------------\n");
        printf("| %s\n", search_entry->filename);
        printf("----------------------------------\n");

        result *result_entry;
        struct list_head *result_pos, *result_tmp;

        list_for_each_prev( result_pos, &(search_entry->results.list) ) {
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
    grepple.pattern = NEW(regex_t);
    int32_t compile_error;

    compile_error = regcomp(grepple.pattern, pattern, 0);

    if ( compile_error ) {
        greppleError("The provided POSIX expression failed to compile\n");
        greppleFree(&grepple);
        exit(EXIT_FAILURE);
    }
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
        // The user is requested help.
        if ( strcmp(argv[i], FLAG_HELP) == 0 ) {
            displayHelp();
            greppleFree(&grepple);
            exit(EXIT_SUCCESS);
        }

        if ( strstr(argv[i], "-ignore") ) {
            printf("woah there\n")  ;

        } else if ( strstr(argv[i], FLAG_PREFIX) ) {
            parseGeneralFlags(argv[i]);
        }
    }
}

int main(int argc, uint8_t **argv) {
    // Incorrect number of arguments, die.
    if ( argc < 2 ) {
        displayHelp();
        exit(EXIT_FAILURE);
    }

    parseFlags(argc, argv);

    // Initialize grepple's internal flags and default values.
    greppleInit(&grepple);

    // Check for silly-ness
    if ( grepple.t_flags & TRAVERSAL_FILE && grepple.t_flags & TRAVERSAL_RECURSIVE ) {
        greppleError("Recursive flag provided with regular file haystack. Ignoring\n");
    }

    // Start the searching routines.
    greppleStart(&grepple);

    // Print results
    displayResults(&grepple);

    // Cleanup
    greppleFree(&grepple);

    exit(EXIT_SUCCESS);
}

