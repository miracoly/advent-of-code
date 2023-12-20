#include "day_03.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LINES_MAX 140
#define LINE_LENGTH_MAX LINES_MAX
#define LINE_LENGTH_MAX_BUF LINE_LENGTH_MAX + 2

static void to_buffer(
        size_t line_length,
        size_t lines,
        FILE *file,
        char buffer[line_length][lines]
);

int main(void) {
    FILE *file = fopen("./input.txt", "r");
    if (!file) return EXIT_FAILURE;

    char buffer[LINES_MAX][LINE_LENGTH_MAX] = {0};
    to_buffer(LINE_LENGTH_MAX, LINES_MAX, file, buffer);

    fclose(file);

    return EXIT_SUCCESS;
}

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
