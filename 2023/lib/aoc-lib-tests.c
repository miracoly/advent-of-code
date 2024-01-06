#include "aoc-lib.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(split, test_1) {
    const char to_split[] = "71 88 83 5 15 54 89 55 69 79";
    const size_t len = strlen(to_split);
    char* expected[] = {"71", "88", "83", "5", "15", "54", "89", "55", "69", "79"};
    char* split_str[len];

    const size_t final_len = aoc_split(len, to_split, split_str);

    cr_expect(eq(uint, final_len, 10));
    for (size_t i = 0; i < final_len; i++) {
        cr_expect(eq(str, split_str[i], expected[i]));
    }
}
