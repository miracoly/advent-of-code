#include "day_04.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <tgmath.h>

Test(get_points_per_card, card_1) {
    const char card[] = "Card   1: 71 88 83  5 15 54 89 55 69 79 | 83 39 58 32 99 54 91 19 44  5 57 29 88  9 95 15 79 71 90 69 43 66 55 12 89";
    const unsigned int points = get_points_per_card(card);
    cr_expect(eq(uint, points, exp2(10 - 1)));
}

Test(get_points_per_card, card_2) {
    const char card[] = "Card   2: 33 11 66 48 67 95 78 71 98 65 | 66  2  1 59 77 95 61 71  8 38 18 62 10 65 53 17 75 92 64 50 67 21 51 78 98";
    const unsigned int points = get_points_per_card(card);
    cr_expect(eq(uint, points, exp2(7 - 1)));
}
