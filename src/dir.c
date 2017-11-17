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
#include "util.h"

#define STRING_EQUALS(s1, s2) (strcmp((s1), (s2)) == 0)

static inline uint8_t isValidDirectory(uint8_t *dir_name) {
    return !STRING_EQUALS(dir_name, ".") != 0 && !STRING_EQUALS(dir_name, "..") != 0;
}

static inline uint8_t isValidFile(greppleData *grepple, uint8_t *file_name) {
    uint8_t valid = 1;

    // Implement a binary file check.
    if ( strstr(file_name, ".dts") != NULL ) {
        valid = 0;
    }

    return valid;
}

void searchDirectory(greppleData *grepple, uint8_t *haystack, uint8_t *needle) {
    stack_push(grepple->current_directory_stack, haystack);
    
    uint8_t *current_working_dir = StringJoin(
        grepple->current_directory_stack->elems,
        grepple->current_directory_stack->top,
        "/"
    );

    DIR *d = opendir(current_working_dir);

    if ( d != NULL ) {
        struct dirent *de;
        
        while ( de = readdir(d) ) {
            switch ( de->d_type ) {
                case DT_REG: // Regular file.
                    if (!isValidFile(grepple, de->d_name)) {
                        break;
                    }

                    // Build out the full path of the current file being searched.
                    size_t file_path_length = strlen(current_working_dir) + strlen("/") + strlen(de->d_name) + 1;
                    char * file_path = (char *) calloc(file_path_length, sizeof(char));
                    strcat(file_path, current_working_dir);
                    strcat(file_path, "/");
                    strcat(file_path, de->d_name);
                    file_path[file_path_length - 1] = '\0';

                    searchFile(grepple, file_path, needle);

                    free(file_path);

                    break;
                case DT_DIR: // Directory
                    if ( grepple->t_flags & TRAVERSAL_RECURSIVE ) {
                        if ( isValidDirectory(de->d_name) ) {
                            searchDirectory(grepple, de->d_name, needle);

                            stack_pop(grepple->current_directory_stack);
                            
                            free(current_working_dir);

                            current_working_dir = StringJoin(
                                grepple->current_directory_stack->elems,
                                grepple->current_directory_stack->top,
                                "/"
                            );
                        }
                    }

                    break;
            }
        }
        
        closedir(d);
    }

    free(current_working_dir);
}

