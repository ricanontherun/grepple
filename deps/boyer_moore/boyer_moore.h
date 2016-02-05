/*
 * Slightly modified implementation of the Boyer-Moore search algorithm, using the "Bad
 * Character" heuristic.
 *
 * The original implementation was taken from http://www.geeksforgeeks.org/pattern-searching-set-7-boyer-moore-algorithm-bad-character-heuristic/.
 */
#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Alphabet size.
#define NUM_OF_CHARS 256

int32_t boyer_moore_search(uint8_t *haystack, uint8_t *needle);

#endif //BOYER_MOORE_H
