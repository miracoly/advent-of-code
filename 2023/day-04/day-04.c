#include "day-04.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "../lib/aoc-lib.h"

unsigned int get_points_per_card(char card[static 1]) {
    char* split1[strlen(card)];
    const size_t len_split1 = aoc_split(strlen(card), card, split1, ":");
    assert(len_split1 == 2);

    char* split2[len_split1];
    const size_t len_split2 = aoc_split(len_split1, split1[1], split2, "|");
    assert(len_split2 == 2);

    char* str_winning_nums = split2[0];
    const size_t len_winning_nums = aoc_reduce_spaces(strlen(str_winning_nums), str_winning_nums);

    char* split3[strlen(str_winning_nums)];
    const size_t n_winning_nums =
            aoc_split(strlen(str_winning_nums), str_winning_nums, split3, " ");

    unsigned long winning_nums[n_winning_nums];
    for (size_t i = 0; i < n_winning_nums; ++i) {
        winning_nums[i] = strtoul(split3[i], 0, 10);
    }

    for (size_t i = 0; i < n_winning_nums; ++i) {
        printf("%lu ", winning_nums[i]);
    }
    printf("\n");

    return len_winning_nums;
}

unsigned int challenge_1(FILE* file) {
    unsigned int total = 0;
    char line[LINE_LENGTH_MAX] = {0};

    while (fgets(line, LINE_LENGTH_MAX, file)) {
        total += get_points_per_card(line);
    }

    return total;
}


