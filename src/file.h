#ifndef FILER_H
#define FILER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

FILE *getFile(char *path, const char *mode);
int getFileType(char *file_path);

#endif
