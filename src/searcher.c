/**
 *  File: searcher.c
 *
 *  Functions for searching files for a keyword.
 */
#include <stdio.h>
#include <string.h>
#include "searcher.h"
#include "match_printer.h"
#include "filer.h"

/**
 *  Search a file for a keyword.
 *  
 *  @param file_path (char *) Full file path
 *  @param search_term (char *) Keyword to search for
 */
void search_for_term(char *file_path, char *search_term) {
    FILE *fp = get_file(file_path, "r");
    char read_block[READ_BLOCK_SIZE];
    int line_count = 0;

    if (fp != NULL) {
        while (fgets(read_block, READ_BLOCK_SIZE, fp) != NULL) {
            if (strchr(read_block, '\n') != NULL)
                line_count++;
            if (strstr(read_block, search_term) != NULL) {
                report_match(stdout, file_path, line_count, read_block); 
            }
        
        }
        fclose(fp);
    }
}
