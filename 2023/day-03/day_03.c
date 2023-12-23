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
    return (c == '*');
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
            row != 0 && col + 1 < LINE_LENGTH_MAX && is_symbol(buffer[row - 1][col + 1]);
    const bool top_left = row != 0 && col != 0 && is_symbol(buffer[row - 1][col - 1]);
    const bool bottom = row < LINES_MAX - 1 && is_symbol(buffer[row + 1][col]);
    const bool bottom_right =
            row < LINES_MAX - 1 && col + 1 < LINE_LENGTH_MAX && is_symbol(buffer[row + 1][col + 1]);
    const bool bottom_left = row < LINES_MAX - 1 && col != 0 && is_symbol(buffer[row + 1][col - 1]);

    return right || left || top || top_right || top_left || bottom || bottom_right || bottom_left;
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

typedef struct {
    bool top_left;
    bool top;
    bool top_right;
    bool left;
    bool right;
    bool bottom_left;
    bool bottom;
    bool bottom_right;
} findings;

static unsigned int get_num_to_left(size_t col, const char buf_line[LINE_LENGTH_MAX]) {
    if (col > LINE_LENGTH_MAX - 1) return 0;

    unsigned int num = 0;
    for (size_t i = col; i < LINE_LENGTH_MAX; --i) {
        const uint8_t e = col - i;
        if (isdigit(buf_line[i])) {
            num += char_to_int(buf_line[i]) * pow10(e);
        } else {
            break;
        }
    }
    return num;
}

static unsigned int get_num_to_right(size_t col, const char buf_line[LINE_LENGTH_MAX]) {
    if (col == LINE_LENGTH_MAX - 1) return 0;

    unsigned int num = 0;
    for (size_t i = col; i < LINE_LENGTH_MAX; ++i) {
        if (isdigit(buf_line[i])) {
            num = (num * 10) + char_to_int(buf_line[i]);
        } else {
            break;
        }
    }
    return num;
}

static unsigned int get_product_of_findings(
        findings f,
        size_t row,
        size_t col,
        const char buffer[LINES_MAX][LINE_LENGTH_MAX]
) {
    const unsigned int left = f.left ? get_num_to_left(col - 1, buffer[row]) : 1;
    const unsigned int right = f.right ? get_num_to_right(col + 1, buffer[row]) : 1;
    const unsigned int top_left =
            f.top_left && !f.top ? get_num_to_left(col - 1, buffer[row - 1]) : 1;
    const unsigned int top_right =
            f.top_right && !f.top ? get_num_to_right(col + 1, buffer[row - 1]) : 1;
    const unsigned int bottom_left =
            f.bottom_left && !f.bottom ? get_num_to_left(col - 1, buffer[row + 1]) : 1;
    const unsigned int bottom_right =
            f.bottom_right && !f.bottom ? get_num_to_right(col + 1, buffer[row + 1]) : 1;
    const unsigned int only_top =
            f.top && !f.top_left && !f.top_right ? char_to_int(buffer[row - 1][col]) : 1;
    const unsigned int top_1 =
            f.top_right && f.top && !f.top_left ? get_num_to_right(col, buffer[row - 1]) : 1;
    const unsigned int top_2 =
            f.top_left && f.top && !f.top_right ? get_num_to_left(col, buffer[row - 1]) : 1;
    const unsigned int top_3 =
            f.top && f.top_left && f.top_right ? get_num_to_left(col + 1, buffer[row - 1]) : 1;
    const unsigned int only_bottom =
            f.bottom && !f.bottom_left && !f.bottom_right ? char_to_int(buffer[row + 1][col]) : 1;
    const unsigned int bottom_1 =
            f.bottom_right && f.bottom && !f.bottom_left ? get_num_to_right(col, buffer[row + 1]) : 1;
    const unsigned int bottom_2 =
            f.bottom_left && f.bottom && !f.bottom_right ? get_num_to_left(col, buffer[row + 1]) : 1;
    const unsigned int bottom_3 =
            f.bottom && f.bottom_left && f.bottom_right ? get_num_to_left(col + 1, buffer[row + 1])
                                                        : 1;

    return left * right * top_left * top_right * bottom_left * bottom_right * only_top * top_1 *
           top_2 * top_3 * only_bottom * bottom_1 * bottom_2 * bottom_3;
}

static unsigned int get_gear_ratio(
        size_t row,
        size_t col,
        const char buffer[LINES_MAX][LINE_LENGTH_MAX]
) {
    const findings f = {
            .top_left = row != 0 && col != 0 && isdigit(buffer[row - 1][col - 1]),
            .top = row != 0 && isdigit(buffer[row - 1][col]),
            .top_right = row != 0 && col + 1 < LINE_LENGTH_MAX &&
                         isdigit(buffer[row - 1][col + 1]),
            .left =  col != 0 && isdigit(buffer[row][col - 1]),
            .right = col + 1 < LINE_LENGTH_MAX && isdigit(buffer[row][col + 1]),
            .bottom_left = row < LINES_MAX - 1 && col != 0 && isdigit(buffer[row + 1][col - 1]),
            .bottom = row < LINES_MAX - 1 && isdigit(buffer[row + 1][col]),
            .bottom_right = row < LINES_MAX - 1 && col + 1 < LINE_LENGTH_MAX &&
                            isdigit(buffer[row + 1][col + 1])
    };

    const uint8_t count_part_nums =
            f.left + f.right
            + (f.top ? 1 : f.top_left + f.top_right)
            + (f.bottom ? 1 : f.bottom_left + f.bottom_right);

    return count_part_nums == 2 ? get_product_of_findings(f, row, col, buffer) : 0;
}

static unsigned long sum_gear_ratios(const char buffer[LINES_MAX][LINE_LENGTH_MAX]) {
    unsigned long total = 0;
    unsigned long findings = 0;
    for (size_t row = 0; row < LINES_MAX; ++row) {
        for (size_t col = 0; col < LINE_LENGTH_MAX; ++col) {
            if (is_symbol(buffer[row][col])) {
                total += get_gear_ratio(row, col, buffer);
                findings++;
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

    unsigned long total = sum_gear_ratios(buffer);

    printf("Result: %lu", total);

    fclose(file);
    return EXIT_SUCCESS;
}
