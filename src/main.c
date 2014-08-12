#include <stdlib.h>
#include <string.h>
#include "init.h"
#include "options.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        grepple_help();
        exit(1);
    }
    unsigned int i = 0;
    unsigned int haystack_i = argc - 2;
    unsigned int needle_i = argc - 1;
    
    grepple_init_resources();

    search_options->haystack = argv[haystack_i];
    search_options->needle = argv[needle_i];

    for (i = 0; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '-') {
            parse_general_flags(argv[i]);
        } else if (strstr(argv[i], "--ignore")) {
            parse_ignore_flags(argv[i]);
        } else if (strstr(argv[i], "--help")) {
            grepple_help();
            grepple_exit(0);
        }
    }

    grepple_init();
    grepple_exit(0);
}
