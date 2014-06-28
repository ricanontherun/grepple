#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "searcher.h"
#include "fs_parser.h"

/**
 *  Feeding this function into the scandir function allows a way to easily check and
 *  regulate which dirent entries are placed in **eps
 */
static int valid_file(const struct dirent *unused) {
    return 1;
}

void print_dir_contents(char *dirname) {
    struct dirent *de;
    DIR *d;

    d = opendir(dirname);

    if (d != NULL) {
        while (de = readdir(d)) {
            switch (de->d_type) {
                case DT_REG:
                    search_for_term(de->d_name, "call_function"); 
                    break;
                case DT_DIR:
                    if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                        print_dir_contents(de->d_name);
                    }
                    break;
            }
        }

        closedir(d);
        return;
    } 
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
