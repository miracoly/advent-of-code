#include "day-01.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"

#define LINE_LENGTH_MAX 2048

static uint8_t get_calibration_of_line(char line[static 1]);

static void update_finding(uint8_t *left, uint8_t *right, uint8_t num);

static uint8_t lookup_number_text(char text[static 1]);

static uint8_t char_to_int(char c);

int main() {
    FILE *file = fopen("./day-01/input.txt", "r");
    if (file == NULL) { return EXIT_FAILURE; }

    printf("Result: %lu\n", get_calibration(file));

    fclose(file);
    return EXIT_SUCCESS;
}

unsigned long get_calibration(FILE *file) {
    unsigned long calibration = 0;
    char line[LINE_LENGTH_MAX] = {0};
    while (fgets(line, LINE_LENGTH_MAX, file)) {
        calibration += get_calibration_of_line(line);
    }
    return calibration;
}

static uint8_t get_calibration_of_line(char line[static 1]) {
    const size_t length = strlen(line);
    uint8_t left = 0;
    uint8_t right = 0;
    for (size_t i = 0; i < length; ++i) {
        if (isdigit(line[i])) {
            update_finding(&left, &right, char_to_int(line[i]));
            continue;
        }

        char potenzial_number[6];
        strncpy(potenzial_number, line + i, 5);
        const uint8_t maybe_num = lookup_number_text(potenzial_number);
        if (UINT8_MAX - maybe_num) {
            update_finding(&left, &right, maybe_num);
        }
    }
    return (left * 10) + right;
}

static void update_finding(uint8_t *left, uint8_t *right, uint8_t num) {
    if (!*left) {
        *left = num;
    }
    *right = num;
}

static uint8_t char_to_int(char c) {
    return c - '0';
}

static uint8_t lookup_number_text(char text[static 1]) {
    if (!strncmp(text, "one", 3)) { return 1; }
    if (!strncmp(text, "two", 3)) { return 2; }
    if (!strncmp(text, "three", 5)) { return 3; }
    if (!strncmp(text, "four", 4)) { return 4; }
    if (!strncmp(text, "five", 4)) { return 5; }
    if (!strncmp(text, "six", 3)) { return 6; }
    if (!strncmp(text, "seven", 5)) { return 7; }
    if (!strncmp(text, "eight", 5)) { return 8; }
    if (!strncmp(text, "nine", 4)) { return 9; }
    else { return UINT8_MAX; }
}
