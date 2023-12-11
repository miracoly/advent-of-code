#include "day_01.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH_MAX 2048

static uint8_t get_calibration_of_line(char line[static 1]);

int main() {
    FILE *file = fopen("./input.txt", "r");
    if (file == NULL) { return EXIT_FAILURE; }

    printf("Result: %lu", get_calibration(file));

    fclose(file);
    return EXIT_SUCCESS;
}

unsigned long get_calibration(FILE *file) {
    unsigned long calibration = 0;
    while (!feof(file)) {
        char line[LINE_LENGTH_MAX];
        fgets(line, LINE_LENGTH_MAX, file);
        calibration += get_calibration_of_line(line);
    }
    return calibration;
}

static uint8_t get_calibration_of_line(char line[static 1]) {
    const size_t length = strlen(line);
    uint8_t left = 0;
    uint8_t right = 0;
    for (size_t i = 0; i < length; ++i) {
        if (left && right) { break; }

        if (isdigit(line[i]) && !left) {
            left = line[i] - '0';
        }
        if (isdigit(line[length - i - 1]) && !right) {
            right = line[length - i - 1] - '0';
        }
    }
    return (!left || !right)
           ? left + right
           : (left * 10) + right;
}
