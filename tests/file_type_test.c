#include <stdio.h>
#include <sys/stat.h>

#include "file.h"

int main(int argc, char *argv[]) {
    printf("%d\n", stat_file_type(argv[1]) == S_IFREG);
    return 0;
}
