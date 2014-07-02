#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fs_parser.h"
#include "searcher.h"

typedef unsigned char u_char;
/**
 *  Feeding this function into the scandir function allows a way to easily check and
 *  regulate which dirent entries are placed in **eps
 */
static int valid_file(const struct dirent *unused) {
    // EMPLOY SOME REGULAR EXPRESSIONS HERE
    // Only allow non-hidden directories
    // and files without ~ and normal .extensions
    return 1;
}

void print_dir_contents(char *dirname, char *search_term) {
    struct dirent *de;
    struct dirent **eps;
    int n;
    int i;

    n = scandir(dirname, &eps, valid_file, alphasort);

    if (n >= 0) {
        for (i = 0; i < n; i++) {
            switch (eps[i]->d_type) {
                case DT_REG:
                    // check_for_term needs the files relative path. Dumbass
                    check_for_term(eps[i]->d_name, search_term); 
                    break;
                case DT_DIR:
                    if (strcmp(eps[i]->d_name, ".") != 0 && strcmp(eps[i]->d_name, "..") != 0 && strchr(eps[i]->d_name, '.') == NULL) {
                        //print_dir_contents(eps[i]->d_name, search_term);
                    }
                    break;
            }
            free(eps[i]);
        }
        free(eps);
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
        fprintf(stderr, "error: Could not open directory.\n");
    }

    free(eps);
}
