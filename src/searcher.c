#include <stdio.h>
#include <string.h>
#include "searcher.h"
#include "match_printer.h"
#include "filer.h"

void search_for_term(char *file_path, char *search_term) {
    FILE *fp = get_file(file_path, "r");
    char read_block[READ_BLOCK_SIZE];
    int line_count = 0;
    int match_count = 0;

    while (fgets(read_block, READ_BLOCK_SIZE, fp) != NULL) {
        if (strchr(read_block, '\n') != NULL)
            line_count++;
        if (strstr(read_block, search_term) != NULL) {
            match_count++;
            report_match(stdout, file_path, line_count, read_block); 
        }
    
    }

    printf("Searched %d lines with %d matches\n", line_count, match_count);
    fclose(fp);
}
