#include "day-04.h"
#include "../lib/aoc-lib.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <tgmath.h>
#include <stdbool.h>

static bool contains(unsigned long num, size_t n_win, unsigned long win_nums[n_win]) {
    for (size_t i = 0; i < n_win; ++i) {
        if (num == win_nums[i]) return true;
    }
    return false;
}

static unsigned long get_points(size_t n_win,
                                unsigned long win_nums[n_win],
                                size_t n_own,
                                unsigned long own_nums[n_own]) {
    size_t count_wins = 0;
    for (size_t i = 0; i < n_own; ++i) {
        if (contains(own_nums[i], n_win, win_nums)) {
            count_wins++;
        }
    }
    return exp2(count_wins - 1);
}

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
            aoc_split(len_winning_nums, str_winning_nums, split3, " ");

    unsigned long winning_nums[n_winning_nums];
    for (size_t i = 0; i < n_winning_nums; ++i) {
        winning_nums[i] = strtoul(split3[i], 0, 10);
    }

    char* str_nums_you_have = split2[1];
    const size_t len_num_you_have = aoc_reduce_spaces(strlen(str_nums_you_have), str_nums_you_have);

    char* split4[strlen(str_nums_you_have)];
    const size_t n_nums_you_have =
            aoc_split(len_num_you_have, str_nums_you_have, split4, " ");

    unsigned long nums_you_have[n_nums_you_have];
    for (size_t i = 0; i < n_nums_you_have; ++i) {
        nums_you_have[i] = strtoul(split4[i], 0, 10);
    }

    return get_points(n_winning_nums, winning_nums, n_nums_you_have, nums_you_have);
}

unsigned int challenge_1(FILE* file) {
    unsigned int total = 0;
    char line[LINE_LENGTH_MAX] = {0};

    while (fgets(line, LINE_LENGTH_MAX, file)) {
        total += get_points_per_card(line);
    }

    return total;
}


