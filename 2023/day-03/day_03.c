#include "day_03.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LINES_MAX 140
#define LINE_LENGTH_MAX 140
#define LINE_LENGTH_MAX_BUF LINE_LENGTH_MAX + 2

static void to_buffer(
        size_t line_length,
        size_t lines,
        FILE *file,
        char buffer[lines][line_length]
) {
    char line[LINE_LENGTH_MAX_BUF];
    size_t current_line = 0;
    while (fgets(line, LINE_LENGTH_MAX_BUF, file) && current_line < lines) {
        for (size_t c = 0; c < line_length; ++c) {
            buffer[current_line][c] = line[c];
        }
        current_line++;
    }
}

static uint8_t char_to_int(char c) {
    return c - '0';
}

static bool is_symbol(char c) {
    return (c != '.') && !isdigit(c);
}

static unsigned int pow10(uint8_t e) {
    unsigned int result = 1;
    for (size_t i = 0; i < e; ++i) {
        result *= 10;
    }
    return result;
}

static bool is_num_included(
        size_t row,
        size_t col,
        const char buffer[LINES_MAX][LINE_LENGTH_MAX]
) {
    const bool right = col + 1 < LINE_LENGTH_MAX
                       && is_symbol(buffer[row][col + 1]);
    const bool left = col != 0 && is_symbol(buffer[row][col - 1]);
    const bool top = row != 0 && is_symbol(buffer[row - 1][col]);
    const bool top_right =
            row != 0
            && col + 1 < LINE_LENGTH_MAX
            && is_symbol(buffer[row - 1][col + 1]);
    const bool top_left =
            row != 0
            && col != 0
            && is_symbol(buffer[row - 1][col - 1]);
    const bool bottom =
            row < LINES_MAX - 1
            && is_symbol(buffer[row + 1][col]);
    const bool bottom_right =
            row < LINES_MAX - 1
            && col + 1 < LINE_LENGTH_MAX
            && is_symbol(buffer[row + 1][col + 1]);
    const bool bottom_left =
            row < LINES_MAX - 1
            && col != 0
            && is_symbol(buffer[row + 1][col - 1]);

    return right || left || top || top_right || top_left || bottom ||
           bottom_right || bottom_left;
}

static int sum_part_numbers(const char buffer[LINES_MAX][LINE_LENGTH_MAX]) {
    unsigned int total = 0;
    for (size_t row = 0; row < LINES_MAX; ++row) {
        unsigned int current_num = 0;
        size_t exp = 0;
        bool did_find_num = false;
        bool is_included = false;
        for (size_t col = LINE_LENGTH_MAX; col != 0; --col) {
            if (isdigit(buffer[row][col - 1])) {
                did_find_num = true;
                current_num += char_to_int(buffer[row][col - 1]) * pow10(exp);
                exp++;
                is_included = is_included || is_num_included(row, col - 1, buffer);
            } else {
                if (did_find_num) {
                    total += is_included ? current_num : 0;
                    is_included = false;
                    current_num = 0;
                    exp = 0;
                }
                did_find_num = false;
            }
            if (col == 1) {
                total += is_included ? current_num : 0;
            }
        }
    }
    return total;
}

int main(void) {
    FILE *file = fopen("./input.txt", "r");
    if (!file) return EXIT_FAILURE;

    char buffer[LINES_MAX][LINE_LENGTH_MAX] = {0};
    to_buffer(LINE_LENGTH_MAX, LINES_MAX, file, buffer);

    unsigned int total = sum_part_numbers(buffer);

    printf("Result: %u", total);

    fclose(file);
    return EXIT_SUCCESS;
}
