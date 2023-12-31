#include <stdio.h>
#include <stdlib.h>
#include "day_04.h"

int main(void) {
    FILE *file = fopen("./input.txt", "r");
    if (!file) {
        perror("Could not open file 'input.txt'.");
        return EXIT_FAILURE;
    }

    printf("Challenge 1 Result: %u\n", challenge_1(file));

    fclose(file);
    return EXIT_SUCCESS;
}
