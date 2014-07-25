#include "../src/fs_parser.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "error: usage %s directory term\n", argv[0]);
        return EXIT_FAILURE;
    }
    open_resources();
    read_dir_contents(argv[1], argv[2]);
    close_resources();
    return EXIT_SUCCESS;
}
