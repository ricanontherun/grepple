#include <stdlib.h>
#include <stdio.h>

#include "dir.h"
#include "../src/init.h"
#include "../src/options.h"

int main(int argc, char *argv[]) {
    init_options(); 

    haystack = ".";
    needle = "grepple";
    grepple_init();
    return EXIT_SUCCESS;
}
