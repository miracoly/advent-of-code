#ifndef INC_2023_AOC_LIB_H
#define INC_2023_AOC_LIB_H

#include <stddef.h>

size_t aoc_split(size_t n, char str[n], char* split_str[n], const char delimiter[static 1]);
size_t aoc_trim(size_t aoc_n, char aoc_str[aoc_n]);
size_t aoc_reduce_spaces(size_t aoc_n, char aoc_str[aoc_n]);

#endif //INC_2023_AOC_LIB_H
