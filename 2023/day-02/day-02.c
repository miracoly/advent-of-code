#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

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

static unsigned int get_id_if_valid(const char line[static 1]);

static unsigned int get_power_of_set(const char line[static 1]);

static unsigned long accumulate_lines(unsigned int acc(const char[LINE_LENGTH_MAX]), FILE *file);

static void add_up(unsigned int target[color_len], color_t color, unsigned int count);

static void put_max(unsigned int target[color_len], color_t color, unsigned int count);

static void do_with_occurrence(
        void handler(unsigned int[], color_t, unsigned int),
        unsigned int target[color_len],
        const char group[static 1]
);

static void remove_new_line(size_t max_len, char str[static max_len]);

int main(void) {
    FILE *file1 = fopen("./day-02/input.txt", "r");
    FILE *file2 = fopen("./day-02/input.txt", "r");
    if (!file1 || !file2) return EXIT_FAILURE;

    printf("Sum valid IDs: %lu\n", accumulate_lines(get_id_if_valid, file1));
    printf("Sum Power: %lu\n", accumulate_lines(get_power_of_set, file2));

    fclose(file1);
    fclose(file2);

    return EXIT_SUCCESS;
}

static color_t find_color(const char name[static 1]) {
    for (color_t i = 0; i < color_len; ++i) {
        if (!strcmp(name, color_name[i])) return i;
    }
    return color_len;
}

static unsigned long accumulate_lines(unsigned int acc(const char[LINE_LENGTH_MAX]), FILE *file) {
    unsigned long result = 0;
    char line[LINE_LENGTH_MAX] = {0};
    while (fgets(line, LINE_LENGTH_MAX, file)) {
        result += acc(line);
    }
    return result;
}

static unsigned int get_id_if_valid(const char line[static 1]) {
    char line_copy[LINE_LENGTH_MAX];
    strncpy(line_copy, line, LINE_LENGTH_MAX - 1);
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
        do_with_occurrence(add_up, occurrence, groups[i]);
        for (color_t c = 0; c < color_len; ++c) {
            if (occurrence[c] > max_quantity[c]) return 0;
        }
    }

    return id;
}

static unsigned int get_power_of_set(const char line[static 1]) {
    char line_copy[LINE_LENGTH_MAX];
    strncpy(line_copy, line, LINE_LENGTH_MAX - 1);
    strtok(line_copy, " ");

    strtok(NULL, ":");
    char *group = strtok(NULL, ";");

    char *groups[GROUPS_MAX];
    size_t group_count = 0;
    while (group != NULL) {
        groups[group_count] = group;
        group = strtok(NULL, ";");
        ++group_count;
    }

    unsigned int occurrence[color_len] = {0};
    for (size_t i = 0; i < group_count; ++i) {
        do_with_occurrence(put_max, occurrence, groups[i]);
    }

    long power = 1;
    for (color_t i = 0; i < color_len; ++i) {
        power *= occurrence[i];
    }

    return power;
}

static void add_up(unsigned int target[color_len], color_t color, unsigned int count) {
    target[color] += count;
}

static void put_max(unsigned int target[color_len], color_t color, unsigned int count) {
    if (count > target[color]) {
        target[color] = count;
    }
}

static void do_with_occurrence(
        void handler(unsigned int[], color_t, unsigned int),
        unsigned int target[color_len],
        const char group[static 1]
) {
    char group_copy[GROUP_LENGTH_MAX];
    strncpy(group_copy, group, GROUP_LENGTH_MAX - 1);

    char *word = strtok(group_copy, " ");
    while (word != NULL) {
        const unsigned int count = atoi(word);
        word = strtok(NULL, ", ");
        remove_new_line(6, word);
        const color_t color = find_color(word);
        handler(target, color, count);
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
