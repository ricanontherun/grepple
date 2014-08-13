/**
 *  File: match_printer.c
 * 
 *  Functions used to print keyword matches to the terminal.
 */
#include <stdio.h>
#include "match_printer.h"

/**
 *  Print a keyword match to the terminal.
 *
 *  @param fp (FILE *) File stream to print to.
 *  @param file_path (char *) File path
 *  @param line_num (unsigned int) Line number which match was found on.
 *  @param match_context (char *) Context in which the match was found.
 */
void report_match(FILE *fp, char *file_path, unsigned int line_num, char *match_context) {
    fprintf(fp, "%s:%u\t%s", file_path, line_num, match_context);
}
