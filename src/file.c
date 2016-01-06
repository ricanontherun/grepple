#include "file.h"

/**
 *  Open a file.
 *
 *  @param path (char *) Full file path
 *  @param mode (const char *) Open mode
 *
 *  @return File pointer or NULL if failure to open.
 */
FILE *getFile(char *path, const char *mode) {
    FILE *fp = fopen(path, mode);

    if (fp == NULL) {
        fprintf(stderr, "grepple: could not open file %s\n", path); 
    }

    return fp;
}

/**
 *  Get a file's type.
 *
 *  @param file_path (char *) Full file path
 *  @return File type as defined in sys/stat.h
 */
int getFileType(char *file_path) {
    struct stat file_stat;

    if ( stat(file_path, &file_stat) < 0 ) {
        fprintf(stderr, "grepple: could not read file %s\n", file_path);
        return 0;
    }

    return (file_stat.st_mode & S_IFMT);
}
