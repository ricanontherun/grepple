/**
 *  File: util.c
 *
 *  Misc. Functions
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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
    char *temp = NULL;
    unsigned int size = 0;
    char *start = s;

    while (*s != '\0') {
        if (*s == delim) {
            temp = malloc(size + 1);
            memcpy(temp, start, size);
            temp[size] = '\0';
            ll_append(list, temp);
            start = s + 1;
            free(temp);
            size = 0;
        } else {
            size++;
        }
        s++;
    }

    if (size != 0) {
        temp = malloc(size + 1);
        memcpy(temp, start, size);
        temp[size] = '\0';
        ll_append(list, temp);
        free(temp);
    }
    
    return;
}
