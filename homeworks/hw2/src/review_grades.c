#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stats.h"

int str_to_int(char *str[]) {
    int val = 0;
    for (int i = 0; i < (int)strlen(*str); i++) {
        char ch = *str[i];

        if (isdigit(ch)) {
            int ch_val = ch - 48;

            val *= val + ch_val;
        } else {
            return -1;
        }
    }

    return val;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "usage: review_grades score1 [score2 ...]\nnote: ignore negative score values");
        return EXIT_FAILURE;
    }

    int input_population = argc - 1;
    int adjusted_population = input_population;
    printf("input population: %d\n", input_population);

    int total = 0;
    int scores[20];

    for (int i = 1; i < argc; i++) {
        int result = strtoll(argv[i], NULL, 10);
        
        if (result <= 0) {
            adjusted_population--;
            continue;
        }

        scores[total] = result;
        total += 1;
        printf("%d ", result);
    }

    printf("\n");
    printf("adjusted population: %d\n", adjusted_population);
    double mean = average(total, scores);
    printf("mean: %f\n", mean);
    printf("std: %.4f\n", std_dev(total, scores, mean));
    histogram(total, scores);

    return EXIT_SUCCESS;
}