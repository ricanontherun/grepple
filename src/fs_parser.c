#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "fs_parser.h"
#include "searcher.h"
#include "stack.h"

typedef unsigned char u_char;
char *current_path;
stack *dir_stk;

/**
 *  Feeding this function into the scandir function allows a way to easily check and
 *  regulate which dirent entries are placed in **eps
 */
int valid_dir(char *dir_name) {
    // EMPLOY SOME REGULAR EXPRESSIONS HERE
    // Only allow non-hidden directories
    // and files without ~ and normal .extensions
    int valid = 1;

    if (strchr(dir_name, '.') != NULL)
        valid = 0;
    return valid;
}

void open_resources() {
    dir_stk = stack_new();
}
void close_resources() {
    free(current_path);
    empty_stack(dir_stk);
}

void print_dir_contents(char *dirname, char *search_term) {
    struct dirent *de;
    struct dirent **eps;
    DIR *d;
    int n;
    int i;

    d = opendir(dirname);
    printf("current working directory: %s\n", current_path);
    if (d != NULL) {
        while (de = readdir(d)) {
            switch (de->d_type) {
                case DT_REG:
                    printf("%s\n", de->d_name);
                    break;
                case DT_DIR:
                    break;
            }
        }
    }
    free(d);
}
