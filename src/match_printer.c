#include <stdio.h>
#include "match_printer.h"

void report_match(FILE *fp, char *file_path, unsigned int line_num, char *match_context) {
    fprintf(fp, "%s @ %u\n\t%s", file_path, line_num, match_context);
}
