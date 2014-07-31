#include <string.h>
#include <stdio.h>
#include "../src/options.h"
#include "../src/init.h"

int main(int argc, char *argv[]) {
    int i = 0;
    
    // Init option defaults
    init_options();

    for (i = 0; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] != '-') {
            parse_general_flags(argv[i]);
        } else if (strstr(argv[i], "--ignore")) {
            parse_ignore_flags(argv[i]);
        }
    }

    printf("%s\n", argv[argc - 2]);
    //grepple_init();
    return 1;
}
