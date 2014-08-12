#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "fs_parser.h"
#include "options.h"
#include "searcher.h"
#include "stack/stack.h"
#include "lists/linked_list.h"

extern grepple_search_options *search_options;

typedef unsigned char u_char;
char *seperator = "/";

unsigned int is_valid_directory(char *dir_name) {
    unsigned int valid = 1;

    if (strchr(dir_name, '.') != NULL) {
        valid = 0;
    }
    
    return valid;
}

unsigned int is_valid_file(char *file_name) {
    unsigned int valid = 1;
    // I'm using strrchr here to allow for file names like jquery.1.9.1.js
    // strrchr wil get the last occurence of the character.
    unsigned char *ext = strrchr(file_name, '.');

    if (strstr(file_name, ".dts") != NULL) {
        valid = 0;
    }

    if (ext != NULL) {
        valid = !ll_node_exists(search_options->ext_ignore_list, ext);
    }

    return valid;
}

void dir_search(char *dirname, char *search_term) {
    struct dirent *de;
    DIR *d;

    // Push directory name on stack
    stack_push(search_options->current_directory_stack, dirname);
    char *current_working_dir = get_dir_path(search_options->current_directory_stack);

    d = opendir(current_working_dir);

    if (d != NULL) {
        while (de = readdir(d)) {
            switch (de->d_type) {
                case DT_REG:
                    ;
                    // Create the full relative path to the current file.
                    if (is_valid_file(de->d_name)) {
                        size_t c_len = strlen(current_working_dir);
                        size_t f_len = strlen(de->d_name); 
                        char *full_file_path = malloc(c_len + f_len + 1);
                        memcpy(full_file_path, current_working_dir, c_len);
                        memcpy(full_file_path + c_len, de->d_name, f_len);
                        full_file_path[c_len + f_len] = '\0';
                        search_for_term(full_file_path, search_term); 
                        free(full_file_path);
                    }
                    break;
                case DT_DIR:
                    if (search_options->search_type == ST_RECURSIVE) {
                        if (is_valid_directory(de->d_name)) {
                            dir_search(de->d_name, search_term);
                            stack_pop(search_options->current_directory_stack);
                            free(current_working_dir);
                            current_working_dir = get_dir_path(search_options->current_directory_stack);
                        }
                    }
                    break;
            }
        }
    }
    free(current_working_dir);
    free(d);
}

char *get_dir_path(stack *s) {
    unsigned int i;
    char *seperator = "/";
    size_t len = strlen(s->elems[0]);
    size_t sep_len = strlen(seperator);
    unsigned int str_len = 0;
    unsigned int next_len = 0;

    char *current_working_dir = malloc(len + 2); 
    memcpy(current_working_dir, s->elems[0], len);
    str_len += len;
    memcpy(current_working_dir + str_len, seperator, sep_len);
    str_len += sep_len;
    current_working_dir[str_len] = '\0';

    for (i = 1; i < s->top; i++) {
        // Record the next elements length
        next_len = strlen(s->elems[i]);

        // Reallocate enough length 
        current_working_dir = realloc(current_working_dir, str_len + next_len + sep_len + 1);
        memcpy(current_working_dir + str_len, s->elems[i], next_len);
        str_len += next_len;

        memcpy(current_working_dir + str_len, seperator, 1);
        str_len += sep_len;
     }
    current_working_dir[str_len] = '\0';
    return current_working_dir;
}
