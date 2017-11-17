#include <stdio.h>
#include <assert.h>
#include <string.h>

// Internal
#include "../src/util.h"

void test_that_it_can_join_strings() 
{
    char * strings[] = {
        "We're",
        "Going",
        "To",
        "Join",
        "These",
        "Strings"
    };

    char * result = StringJoin(strings, 6, "/");

    assert(strcmp(result, "We're/Going/To/Join/These/Strings") == 0);

    free(result);
}

int main() {
    test_that_it_can_join_strings();
}
