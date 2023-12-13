#include "day_02.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LENGTH_MAX 2024
#define GROUP_LENGTH_MAX 2024
#define GROUPS_MAX 20

typedef enum {
    red, green, blue, color_len
} color_t;

static char const *const color_name[color_len] = {
        [red] = "red",
        [green] = "green",
        [blue] = "blue",
};

static uint8_t const max_quantity[color_len] = {
        [red] = 12,
        [green] = 13,
        [blue] = 14,
};

static uint8_t get_id_if_invalid(char line[static 1]);

static void add_occurrence(unsigned int target[color_len], const char group[static 1]);

static void remove_new_line(size_t max_len, char str[static max_len]);

int main(void) {
    FILE *file = fopen("./input.txt", "r");
    if (file == NULL) return EXIT_FAILURE;

    printf("Result: %lu\n", get_sum_of_valid_ids(file));

    fclose(file);
    return EXIT_SUCCESS;
}

static color_t find_color(const char name[static 1]) {
    for (color_t i = 0; i < color_len; ++i) {
        if (!strcmp(name, color_name[i])) return i;
    }
    return color_len;
}

unsigned long get_sum_of_valid_ids(FILE *file) {
    unsigned long sum_ids = 0;
    while (!feof(file)) {
        char line[LINE_LENGTH_MAX];
        fgets(line, LINE_LENGTH_MAX, file);
        sum_ids += get_id_if_invalid(line);
    }
    return sum_ids;
}

static uint8_t get_id_if_invalid(char line[static 1]) {
    char line_copy[LINE_LENGTH_MAX];
    strncpy(line_copy, line, LINE_LENGTH_MAX);
    strtok(line_copy, " ");

    const int id = atoi(strtok(NULL, ":"));
    char *group = strtok(NULL, ";");

    char *groups[GROUPS_MAX];
    size_t group_count = 0;
    while (group != NULL) {
        groups[group_count] = group;
        group = strtok(NULL, ";");
        ++group_count;
    }

    for (size_t i = 0; i < group_count; ++i) {
        unsigned int occurrence[color_len] = {0};
        add_occurrence(occurrence, groups[i]);
        for (color_t c = 0; c < color_len; ++c) {
            if (occurrence[c] > max_quantity[c]) return 0;
        }
    }

    return id;
}

static void add_occurrence(unsigned int target[color_len], const char group[static 1]) {
    char group_copy[GROUP_LENGTH_MAX];
    strncpy(group_copy, group, GROUP_LENGTH_MAX);

    char *word = strtok(group_copy, " ");
    while (word != NULL) {
        const int count = atoi(word);
        word = strtok(NULL, ", ");
        remove_new_line(6, word);
        const color_t color = find_color(word);
        target[color] += count;
        word = strtok(NULL, " ");
    }
}

static void remove_new_line(size_t max_len, char str[static max_len]) {
    for (size_t i = 0; i < max_len; ++i) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}
