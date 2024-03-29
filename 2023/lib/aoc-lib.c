#include "aoc-lib.h"
#include <string.h>
#include <ctype.h>

/**
 * Split string into list of string.
 * @param aoc_n Length of \p aoc_str
 * @param aoc_str String to split
 * @param aoc_split_str List of strings to hold result
 * @param aoc_delimiter Delimiter to split on
 * @return List of split strings
 */
size_t aoc_split(size_t aoc_n,
                 char aoc_str[aoc_n],
                 char* aoc_split_str[aoc_n],
                 const char aoc_delimiter[static 1]) {
    char* found_str = strtok(aoc_str, aoc_delimiter);
    size_t len = 0;

    while (len < aoc_n && found_str) {
        aoc_split_str[len] = found_str;
        found_str = strtok(NULL, aoc_delimiter);
        len++;
    }

    return len;
}

/**
 * Removes leading and trailing white space.
 * @param aoc_n Length of \p aoc_str
 * @param aoc_str String to trim
 * @return New length of trimmed string
 */
size_t aoc_trim(size_t aoc_n, char aoc_str[aoc_n]) {
    size_t l = 0;
    size_t r = aoc_n - 1;

    while (isspace(aoc_str[l]) && l < aoc_n) l++;
    while (isspace(aoc_str[r])) r--;

    if (l > r) return 0;

    size_t len = r - l + 1;
    for (size_t i = 0; i < len; ++i) {
        aoc_str[i] = aoc_str[l + i];
    }
    aoc_str[len] = '\0';

    return len;
}

/**
 * Trims and reduces consecutive spaces to one space.
 * @param aoc_n Length of \p aoc_str
 * @param aoc_str String to clean
 * @return New length of reduced string
 */
size_t aoc_reduce_spaces(size_t aoc_n, char aoc_str[aoc_n]) {
    size_t n_trimmed = aoc_trim(aoc_n, aoc_str);
    size_t len = 0;

    for (size_t i = 0; i < (n_trimmed); ++i) {
        if (isspace(aoc_str[i]) && isspace(aoc_str[i + 1])) continue;

        aoc_str[len] = aoc_str[i];
        len++;
    }
    aoc_str[len] = '\0';

    return len;
}
