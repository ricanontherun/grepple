#ifndef SEARCH_H
#define SEARCH_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../deps/linux/list.h"
#include "grepple.h"
#include "file.h"

#define READ_BLOCK_SIZE 100

void searchFile(greppleData *grepple, uint8_t *file_path, uint8_t *search_term);

#endif
