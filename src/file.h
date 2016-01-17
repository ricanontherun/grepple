#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

FILE *getFile(uint8_t *path, const uint8_t *mode);
int getFileType(uint8_t *file_path);

#endif
