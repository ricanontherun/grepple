#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"
#include "grepple.h"
#include "lists/linked_list.h"
#include "stack/stack.h"

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

void initGrepple() {
    grepple.ext_ignore_list = ll_new();
    grepple.current_directory_stack = stack_new();
}

void destroyGrepple() {

}

void freeResources() {

}

int main(int argc, char *argv[]) {
    // Honestly, we should do ALL option/flag checking here.
    if (argc < 3) {
        display_help();
        exit(1);
    }

    initGrepple();

    unsigned int i = 0;
    unsigned int haystack_i = argc - 2;
    unsigned int needle_i = argc - 1;


//    grepple->haystack = argv[haystack_i];
//    grepple->needle = argv[needle_i];
//
//    for (i = 0; i < argc; i++) {
//        if (argv[i][0] == '-' && argv[i][1] != '-') {
//            parse_general_flags(argv[i]);
//        } else if (strstr(argv[i], "--ignore")) {
//            parse_ignore_flags(argv[i]);
//        } else if (strstr(argv[i], "--help")) {
//            display_help();
//            grepple_exit(0);
//        }
//    }
//
//    grepple_init();
//    grepple_exit(0);
}
