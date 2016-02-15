#include <stdio.h>
#include "output.h"

/**
 *  Print a keyword match to the terminal.
 *
 *  @param fp (FILE *) File stream to print to.
 *  @param file_path (char *) File path
 *  @param line_num (unsigned int) Line number which match was found on.
 *  @param match_context (char *) Context in which the match was found.
 */
void report_match(FILE *fp, char *file_path, unsigned int line_num, char *match_context) {
    fprintf(fp, ":%u\t%s", line_num, match_context);
}

void print_result(uint32_t line_number, char *context) {

}
