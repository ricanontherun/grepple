#include "fs_parser.h"

int main() {
    open_resources();
    read_dir_contents("linux-master", "test");
    close_resources();
    return EXIT_SUCCESS;
}
