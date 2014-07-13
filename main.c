#include "fs_parser.h"

int main() {
    open_resources();
    print_dir_contents(".", "asd");
    close_resources();
    return 0;
}
