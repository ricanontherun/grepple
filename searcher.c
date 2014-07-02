#include <stdio.h>
#include <string.h>
#include "searcher.h"

void check_for_term(char *file_path, char *filename, char *search_term) {
    FILE *fp = fopen(filename, "r");
    char s[READ_BLOCK_SIZE];
    int line_count = 0;

    printf("File path: %s\n", *dir_path);
    while (fgets(s, READ_BLOCK_SIZE, fp) != NULL) {
        if (strchr(s, '\n') != NULL)
            line_count++;

        if (strstr(s, search_term) != NULL)
            printf("%s: %s found on line %d\n\t%s", filename, search_term, line_count, s);
    
    }
    fclose(fp);
}
