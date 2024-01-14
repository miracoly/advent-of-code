#include "aoc-lib.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(aoc_split, empty_string) {
    char to_split[] = "";
    const size_t len = strlen(to_split);
    char* split_str[len];

    const size_t final_len = aoc_split(len, to_split, split_str, " ");

    cr_expect(eq(uint, final_len, 0));
}

Test(aoc_split, test_1) {
    char to_split[] = "71 88 83 5 15 54 89 55 69 79";
    const size_t len = strlen(to_split);
    char* expected[] = {"71", "88", "83", "5", "15", "54", "89", "55", "69", "79"};
    char* split_str[len];

    const size_t final_len = aoc_split(len, to_split, split_str, " ");

    cr_expect(eq(uint, final_len, 10));
    for (size_t i = 0; i < final_len; i++) {
        cr_expect(eq(str, split_str[i], expected[i]));
    }
}

Test(aoc_split, test_2) {
    char to_split[] = "71";
    const size_t len = strlen(to_split);
    char* expected[] = {"71"};
    char* split_str[len];

    const size_t final_len = aoc_split(len, to_split, split_str, " ");

    cr_expect(eq(uint, final_len, 1));
    for (size_t i = 0; i < final_len; i++) {
        cr_expect(eq(str, split_str[i], expected[i]));
    }
}

Test(aoc_trim, empty_string) {
    char before[] = "";
    const size_t len = strlen(before);
    char expected[] = "";

    const size_t final_len = aoc_trim(len, before);

    cr_expect(eq(uint, final_len, strlen(expected)));
    cr_expect(eq(str, before, expected));
}

Test(aoc_trim, test_1) {
    char before[] = "   71  88   83 5 15   54 89 55 69 79";
    const size_t len = strlen(before);
    char expected[] = "71  88   83 5 15   54 89 55 69 79";

    const size_t final_len = aoc_trim(len, before);

    cr_expect(eq(uint, final_len, strlen(expected)));
    cr_expect(eq(str, before, expected));
}

Test(aoc_trim, test_2) {
    char before[] = "   71  88   83 5 15   54 89 55 69 79   ";
    const size_t len = strlen(before);
    char expected[] = "71  88   83 5 15   54 89 55 69 79";

    const size_t final_len = aoc_trim(len, before);

    cr_expect(eq(uint, final_len, strlen(expected)));
    cr_expect(eq(str, before, expected));
}

Test(aoc_reduce_spaces, test_1, .disabled = true) {
    char before[] = " 71  88   83 5 15   54 89 55 69 79   ";
    const size_t len = strlen(before);
    char expected[] = "71 88 83 5 15 54 89 55 69 79";

    const size_t final_len = aoc_reduce_spaces(len, before);

    cr_expect(eq(uint, final_len, strlen(expected)));
    cr_expect(eq(str, before, expected));
}
