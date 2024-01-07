#include "aoc-lib.h"
#include <string.h>

size_t aoc_split(size_t n, char str[n], char* split_str[n], const char delimiter[static 1]) {
    char* found_str = strtok(str, delimiter);
    size_t len = 0;

    while (len < n && found_str) {
        split_str[len] = found_str;
        found_str = strtok(NULL, delimiter);
        len++;
    }

    return len;
}
