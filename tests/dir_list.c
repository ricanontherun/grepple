#include <string.h>
#include <stdio.h>
#include "../src/fs_parser.h"
#include <stdlib.h>

int main() {
    open_resources();
    print_dir_contents("linux-master", "test");
    close_resources();
    return EXIT_SUCCESS;
}
