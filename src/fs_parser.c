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

    stack_push(dir_stk, dirname);
    free(current_path);
    get_dir_path(dir_stk);
    d = opendir(current_path);
    printf("current working directory: %s\n", current_path);
    if (d != NULL) {
        while (de = readdir(d)) {
            switch (de->d_type) {
                case DT_REG:
                    break;
                case DT_DIR:
                    if (valid_dir(de->d_name)) {
                        print_dir_contents(de->d_name, search_term);
                        stack_pop(dir_stk);
                        free(current_path);
                        get_dir_path(dir_stk);
                    }
                    break;
            }
        }
    }
    free(d);
}

void get_dir_path(stack *s) {
    int i;
    current_path = (char *)malloc(strlen(s->elems[0]));
    int str_len = 1;

    if (current_path != NULL) {
        for (i = 0; i < s->top; i++) {
            str_len++;
            current_path = (char *) realloc(current_path, (str_len * sizeof(s->elems[i])) + 1);
            strcat(current_path, s->elems[i]);
            strcat(current_path, "/");
        }
    }

    return;
}
