#include "../src/fs_parser.h"
#include <stdlib.h>

int main() {
    open_resources();
    read_dir_contents(".", "var");
    close_resources();
    return EXIT_SUCCESS;
}
