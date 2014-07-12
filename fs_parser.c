#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "fs_parser.h"
#include "searcher.h"

typedef unsigned char u_char;
char s[1024];

/**
 *  Feeding this function into the scandir function allows a way to easily check and
 *  regulate which dirent entries are placed in **eps
 */
static int valid_file(const struct dirent *unused) {
    // EMPLOY SOME REGULAR EXPRESSIONS HERE
    // Only allow non-hidden directories
    // and files without ~ and normal .extensions
    return 1;
}

void print_dir_contents(char *dirname, char *search_term) {
    struct dirent *de;
    struct dirent **eps;
    DIR *d;
    int n;
    int i;

    d = opendir(dirname);
    if (d != NULL) {
        while (de = readdir(d)) {
            switch (de->d_type) {
                case DT_REG:
                    printf("File: %s\n", de->d_name);
                    break;
                case DT_DIR:
                    printf("Dir : %s\n", de->d_name);
                    break;
            }
        }
    }
    free(d);
    /*
    n = scandir("./test_dir/testicle_2/", &eps, valid_file, alphasort);

    if (n >= 0) {
        for (i = 0; i < n; i++) {
            switch (eps[i]->d_type) {
                case DT_REG:
                    // check_for_term needs the files relative path. Dumbass
                    //check_for_term("./", eps[i]->d_name, search_term); 
                    break;
                case DT_DIR:
                    if (strcmp(eps[i]->d_name, ".") != 0 && strcmp(eps[i]->d_name, "..") != 0 && strchr(eps[i]->d_name, '.') == NULL) {
                        strcat(s, "/");
                        strcat(s, eps[i]->d_name);
                        printf("Entering directory %s\n", s);
                        print_dir_contents(eps[i]->d_name, search_term);
                        printf("Leaving directory %s\n", s);
                    }
                    break;
            }
            free(eps[i]);
        }
        free(eps);
        return;
    } 

    */
}
