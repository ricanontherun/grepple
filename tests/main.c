#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i = 0;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            printf("Found config rule\n");
        }
    }

    return EXIT_SUCCESS;
}
