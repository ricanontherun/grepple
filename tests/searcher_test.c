/*
    Unit test for search_for_term
 */
#include <stdio.h>
#include <stdlib.h>
#include "searche.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s: error:\n\tusage %s search_term\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }
    search_for_term("test.c", argv[1]);
    return EXIT_SUCCESS;
}
