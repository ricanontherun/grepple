/*
    Linked list test.
    Read bytes from a file into the linked list.
*/
#include <stdio.h>
#include <string.h>
#include "../src/filer.h"
#include "../src/lists/linked_list.h"

void string_split_to_ll(char *s, linked_list *list) {
    unsigned char ext[10];
    unsigned char i = 0;

    while (*s != '\0') {
        if (*s != ',') {
            ext[i++] = *s;
        } else {
            ext[i] = '\0';
            ll_append(list, ext);
            i = 0;
        }
        s++;
    }
    ext[i] = '\0';
    if (strlen(ext)) {
        ll_append(list, ext);
    }
}

linked_list *parse_ignore_flags(char *s) {
    unsigned short i;
    unsigned char *lbp = strchr(s, '[');
    unsigned char *rbp = strchr(s, ']');
    unsigned char *p;
    size_t len = strlen(s);
    unsigned char ig_opts[len];

    if (lbp && rbp && (lbp < rbp)) {
        p = ++lbp;
        i = 0;

        while (*p != ']') {
            ig_opts[i++] = *p;
            p++;
        }

        ig_opts[i] = '\0';
        linked_list *ig_list = ll_new();
        string_split_to_ll(ig_opts, ig_list);
        return ig_list;
    } else {
        printf("Displaying grepple help...\n");
        return NULL;
    }
}

int main(int argc, char *argv[]) {
    unsigned char i;

    for (i = 0; i < argc; i++) {
        if (strstr(argv[i], "--ignore")) {
            linked_list *ig_list = parse_ignore_flags(argv[i]);
            ll_print_list(ig_list);
            ll_free_list(ig_list);
        }
    }
    return 1;
}
