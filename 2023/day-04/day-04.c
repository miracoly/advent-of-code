#include "day-04.h"
#include <stdio.h>

unsigned int get_points_per_card(const char card[static 1]) {
    return 1;
}

unsigned int challenge_1(FILE* file) {
    unsigned int total = 0;
    char line[LINE_LENGTH_MAX] = {0};

    while (fgets(line, LINE_LENGTH_MAX, file)) {
        total += get_points_per_card(line);
    }

    return total;
}


