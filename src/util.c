#include "util.h"

char *trim(char *s) {
    LTRIM(s);
    RTRIM(s);
    return s;
}

char * StringJoin(char ** strings, size_t length, char * delim) {
    // The number of delimiters we will need.
    size_t num_delim = length > 1 ? length - 1 : 0;

    // Start figuring out how much space we will need for our buffer.
    // 1 for '\0' plus all of the delimiters.
    size_t string_length = 1 + (strlen(delim) * num_delim);

    // Add on the lengths of the various strings.
    for (size_t i = 0; i < length; i++) {
        string_length += strlen(strings[i]);
    }

    // Create a buffer of the required size.
    char * result = (char *) calloc(string_length, sizeof(char));
    
    // Insert stuff into the buffer.
    for (size_t i = 0, j = 0; i < length; i++) {
        // Append the string
        strcat(result, strings[i]);

        // Append the delimiter
        if (j++ < num_delim) {
            strcat(result, delim); 
        } 
    }

    result[string_length - 1] = '\0';

    return result;
}
