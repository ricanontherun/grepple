#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "ts_main.h"
#define READ_BLOCK_SIZE 1024

void print_file(char *filename, char *search_term) {
    FILE *fp = fopen(filename, "r");
    char s[READ_BLOCK_SIZE];
    int line_count = 0;

    while (fgets(s, READ_BLOCK_SIZE, fp) != NULL) {
        if (strchr(s, '\n') != NULL)
            line_count++;

        if (strstr(s, search_term) != NULL)
            printf("%s: %s found on line %d\n\t%s", filename, search_term, line_count, s);
    
    }
    fclose(fp);
}

void print_fs(char *term) {
    DIR *d = opendir(".");
    struct dirent *ep;

    if (d != NULL) {
        while (ep = readdir(d)) {
            switch (ep->d_type) {
                case DT_DIR:
                    // Enter directory recursively
                    break;
                case DT_REG:
                    print_file(ep->d_name, term);
                    break;
            }
        }
    } else {
        fprintf(stderr, "Failed to open directory", NULL);
    }
    closedir(d);
}

void print_dir(struct dirent *dir) {
    
}

int main(int argc, char *argv[]) {
    ts_init();
    return 0;
}
