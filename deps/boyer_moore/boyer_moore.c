#include <stdio.h>

#include "boyer_moore.h"

int max(int a, int b) { return ( a > b ) ? a : b; }
static void bad_character_heuristic(uint8_t *str, uint32_t size, int32_t *bad_character) {
    uint32_t i;

    // Initialize occurrences.
    for ( i = 0; i < NUM_OF_CHARS; i++ ) {
        bad_character[i] = -1;
    }

    /**
     * For each character in str, record index of it's last occurrence.
     */
    for ( i = 0; i < size; i++ ) {
       bad_character[(uint8_t) str[i]] = i;
    }
}

int32_t boyer_moore_search(uint8_t *haystack, uint8_t *needle) {
    size_t needle_length = strlen(needle);
    size_t haystack_length = strlen(haystack);
    int32_t index = -1;

    if ( needle_length > haystack_length ) {
        return index;
    }

    // Pre-process the needle.
    int32_t bad_character[NUM_OF_CHARS];
    bad_character_heuristic(needle, needle_length, bad_character);

    // S is the shift of the needle.
    int32_t shift = 0;
    size_t difference = haystack_length - needle_length;

    while ( shift <= difference ) {
        int32_t j = needle_length - 1;

        /**
         * We're doing simple comparison. We start comparing the end of the needle with it's related section
         * in the haystack. Decreasing j each successful match shifts the needle to the right.
         */
        while ( j >= 0 && needle[j] == haystack[shift + j] ) {
            j--;
        }

        if ( j < 0 ) {
            index = shift;
            shift += ( shift + needle_length < haystack_length ) ?
                 needle_length - bad_character[haystack[shift + needle_length]] : 1;
        } else { //
            shift += max(1, j - bad_character[haystack[shift + j]]);
        }
    }

    return index;
}
