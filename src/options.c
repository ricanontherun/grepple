/**
 *  File: options.c
 *
 *  Functions used to parse command line arguments and populate the grepple struct.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "grepple.h"
#include "options.h"
#include "lists/linked_list.h"
#include "util.h"
#include "init.h"

extern greppleData *grepple;

/**
 *  Parse general flags (Recursive, at the moment)
 *
 *  @param flags (char *) String in (hopefully) correct -flags format.
 */
void parse_general_flags(char *flags) {
    unsigned int i;
    for (i = 1; i < strlen(flags); i++) {
        switch (flags[i]) {
            case 'r':
                grepple->search_type = ST_RECURSIVE;
                break;
            default:
                break;
        }
    }
}

/**
 *  Parse ignore flags in the form --ignore[COMMA SEPERATE LIST]
 *
 *  @param s (char *) String in the form --ignore[COMMA SEPERATED LIST]
 */
void parse_ignore_flags(char *s) {
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
        string_split_to_ll(ig_opts, grepple->ext_ignore_list, ',');
    } else {
        grepple_free_resources();
        exit(EXIT_FAILURE);
    }
}
