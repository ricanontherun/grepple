/**
 *  File: util.c
 *
 *  Misc. Functions
 */
#include <string.h>
#include <stdio.h>

#include "util.h"
#include "lists/linked_list.h"

/**
 *  Split a string into a linked list.
 *
 *  @param s (char *) string to be split
 *  @param list (linked_list *) linked list
 *  @param delim (char) character to split s on
 */
void string_split_to_ll(char *s, linked_list *list, char delim) {
    unsigned char ext[10]; // LIMIT THE LENGTH OF AN EXTENSION or do it with malloc
    unsigned int i = 0;
    unsigned int curr_pos = 0;
    unsigned int start_pos = 0;
    char *t = s;

    while (*s != '\0') {
        if (*s != delim) {
            ext[i++] = *s;
            curr_pos++;
        } else {
            ext[i] = '\0';
            ll_append(list, ext);
            printf("start pos: %c\n", *(t + start_pos));

            start_pos = curr_pos - 1;
            printf("end pos: %c\n", *(t + start_pos + curr_pos));
            i = 0;
        }
        s++;
    }
    ext[i] = '\0';

    if (strlen(ext)) {
        ll_append(list, ext);
    }
}
