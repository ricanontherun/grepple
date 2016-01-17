#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "search.h"
#include "dir.h"
#include "grepple.h"
#include "stack/stack.h"
#include "lists/linked_list.h"

extern greppleData grepple;

char *seperator = "/";

uint8_t isValidDirectory(uint8_t *dir_name) {
    uint8_t valid = 1;

    if ( strchr(dir_name, '.') != NULL ) {
        valid = 0;
    }
    
    return valid;
}

uint8_t isValidFile(uint8_t *file_name) {
    uint8_t valid = 1;

    // Implement a binary file check.
    if ( strstr(file_name, ".dts") != NULL ) {
        valid = 0;
    }

    if ( grepple.ext_ignore_list != NULL ) {
        uint8_t *ext = strrchr(file_name, '.');
        if (ext != NULL && ll_node_exists(grepple.ext_ignore_list, ext)) {
            valid = 0; 
        }
    }

    return valid;
}

// TODO: All this function does is implode a linked list to a string.
// Remove this nasty-ness  from this file and rename. listImplode(delimiter, list);
char *getWorkingDirectory(stack *s) {
    unsigned int i;
    uint8_t *seperator = "/";
    size_t len = strlen(s->elems[0]);
    size_t sep_len = strlen(seperator);
    unsigned int str_len = 0;
    unsigned int next_len = 0;

    uint8_t *current_working_dir = malloc(len + 2);
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

void searchDirectory(uint8_t *haystack, uint8_t *needle) {
    struct dirent *de;
    DIR *d;

    // Push directory name on stack
    stack_push(grepple.current_directory_stack, haystack);
    uint8_t *current_working_dir = getWorkingDirectory(grepple.current_directory_stack);

    d = opendir(current_working_dir);

    if ( d != NULL ) {
        while ( de = readdir(d) ) {
            switch ( de->d_type ) {
                case DT_REG: // Non-Directory
                    if ( isValidFile(de->d_name) ) {
                        size_t c_len = strlen(current_working_dir);
                        size_t f_len = strlen(de->d_name); 
                        char *full_file_path = malloc(c_len + f_len + 1);
                        memcpy(full_file_path, current_working_dir, c_len);
                        memcpy(full_file_path + c_len, de->d_name, f_len);
                        full_file_path[c_len + f_len] = '\0';
                        searchFile(grepple, full_file_path, needle);
                        free(full_file_path);
                    }
                    break;
                case DT_DIR: // Directory
                    if ( grepple.search_type == SEARCH_TYPE_RECURSIVE ) {
                        if ( isValidDirectory(de->d_name) ) {
                            searchDirectory(de->d_name, needle);

                            // Whenever we leave a recursive directory search remove that directory from
                            // the directory stack and construct the working directory string.
                            stack_pop(grepple.current_directory_stack);
                            free(current_working_dir);
                            current_working_dir = getWorkingDirectory(grepple.current_directory_stack);
                        }
                    }
                    break;
            }
        }
    }

    closedir(d);
    free(current_working_dir);
}

