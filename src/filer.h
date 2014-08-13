#ifndef FILER_H
#define FILER_H

FILE *get_file(char *path, const char *mode);
int stat_file_type(char *file_path);

#endif
