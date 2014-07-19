#include <string.h>
#include <stdio.h>
#include "../src/stack.h"
#include "../src/fs_parser.h"
#include <stdlib.h>

#define NEW_STR(str, mul, add) (malloc(strlen(str) * mul + add))
#define END_STR(str) (str[strlen(str)] = '\0')

char *current_working_dir = NULL;

void get_dir_path(stack *s) {
    int i;
    char *seperator = "/";
    size_t len = strlen(s->elems[0]);
    size_t sep_len = strlen(seperator);
    int str_len = 0;
    int next_len = 0;

    // Get memory for the first element
    // and two extra bytes, one for the seperator and one for the terminating character.
    current_working_dir = malloc(len + 2); 

    // Copy the first stack element to the string.
    memcpy(current_working_dir, s->elems[0], len);

    // Copy the seperator to the string.
    str_len += len;
    memcpy(current_working_dir + str_len, seperator, sep_len);

    // Record the new string length (first element length  + seperator length)
    str_len += sep_len;

    // Terminate the string
    current_working_dir[str_len] = '\0';

    for (i = 1; i < s->top; i++) {
        // Record the next elements length
        next_len = strlen(s->elems[i]);

        // Reallocate enough length 
        current_working_dir = realloc(current_working_dir, str_len + next_len + sep_len + 1);
        memcpy(current_working_dir + str_len, s->elems[i], next_len);
        str_len += next_len;

        memcpy(current_working_dir + str_len, seperator, 1);
        str_len += sep_len;
     }
    current_working_dir[str_len] = '\0';
    printf("Current string length: %d\n", str_len);
    return;
    // get memory for the first element
    // loop
    // realloc for strlen(c) + strlen(next) + strlen(seperator)
    // memcpy all
    // out of loop
    // realloc for strlen(c) + 1
    // end string
    if (current_working_dir != NULL) {
        for (i = 0; i < s->top; i++) {
            str_len++;
            current_working_dir = (char *) realloc(current_working_dir, (str_len * sizeof(s->elems[i])) + 3);
            strcat(current_working_dir, s->elems[i]);
            strcat(current_working_dir, "/");
            END_STR(current_working_dir);
        }
    }

    return;
}

int main() {
    char *seperator = "/";
    stack *stk = stack_new();
    // Push some ish on the stack.
    stack_push(stk, ".");

    /*
    size_t len = strlen(stk->elems[0]);
    // Allocate enough memory for the first string, the second string and the terminator
    current_working_dir = malloc(len + 2); 

    // Copy the first stack element to memory
    memcpy(current_working_dir, stk->elems[0], strlen(stk->elems[0]));

    // Copy the seperator to the end of the string
    // len = the length of the first part, so ptr + strlen(ptr) advances the pointer to the end of the string
    // exactly where we want to start copying
    memcpy(current_working_dir + len, seperator, strlen(seperator) + 1);

    // terminate the string. VERY IMPORTANT
    END_STR(current_working_dir);
    */
    
    get_dir_path(stk);
    print_dir_contents(current_working_dir, "test");
    printf("%s\n", current_working_dir);
    free(current_working_dir);
    empty_stack(stk);
    return EXIT_SUCCESS;
}
