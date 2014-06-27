#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "searcher.h"
#include "fs_parser.h"

/**
 *  Feeding this function into the scandir function allows a way to easily check and
 *  regulate which dirent entries are placed in **eps
 */
static int valid_file(const struct dirent *unused) {
    return 1;
}

void start_dir_loop() {
    struct dirent **eps;
    int i;
    int n;
    n = scandir("./", &eps, valid_file, alphasort);

    if (n >= 0) {
        int cnt;

        for (cnt = 0; cnt < n; cnt++) {
            check_for_term(eps[cnt]->d_name, "call_function");
            free(eps[cnt]);
        }
    } else {
        fprintf(stderr, "error: Could not open directory.\n", NULL);
    }

    free(eps);
}
