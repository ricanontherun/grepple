#include <stdio.h>
#include <stdlib.h>
#include "filer.h"

FILE *get_file(char *path, const char *mode) {
    FILE *fp = fopen(path, mode);

    if (fp == NULL) {
        fprintf(stderr, "grepple: could not open file %s\n", path); 
        exit(EXIT_FAILURE);
    } else {
        return fp;
    }
}
