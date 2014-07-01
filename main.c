#include "ts_main.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s search-term\n", argv[0]);
        exit(0);
    }

    ts_init(argv[1]);
    return 0;
}
