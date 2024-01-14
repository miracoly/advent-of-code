#include "day-04.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE* file = fopen("./day-04/input.txt", "r");
    if (!file) {
        perror("Could not open file 'input.txt'.");
        return EXIT_FAILURE;
    }

    printf("Challenge 1 Result: %u\n", challenge_1(file));

    fclose(file);
    return EXIT_SUCCESS;
}
