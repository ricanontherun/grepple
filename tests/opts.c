#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../src/options.h"
#include "../src/init.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        grepple_help();
        exit(EXIT_FAILURE);
    }
    int i = 0;
    int haystack_i = argc - 2;
    int needle_i = argc - 1;
    
    // Init option defaults
    init_options();

    for (i = 0; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '-') {
            parse_general_flags(argv[i]);
        } else if (strstr(argv[i], "--ignore")) {
            parse_ignore_flags(argv[i]);
        } else if (strstr(argv[i], "--help")) {
            grepple_help();
            exit(EXIT_SUCCESS);
        }
    }

    haystack = argv[haystack_i];
    needle = argv[needle_i];
    grepple_init();
    return EXIT_SUCCESS;
}
