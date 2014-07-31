#ifndef OPTIONS_H
#define OPTIONS_H

#define ST_RECURSIVE 0
#define ST_REGULAR 1
#define ST_SINGLE_FILE 2

unsigned char search_type;

extern void init_option();
extern void parse_general_flags(char *flags);
extern void parse_ignore_flags(char *ignore_str);
#endif
