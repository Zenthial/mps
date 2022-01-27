// 
// File: review_grades.c
// Description: Contains the main program entry point, as well as the str_to_int helper function
// 
// @author tss2344: Thomas Schollenberger
// 
// // // // // // // // // // // // // // // // // // // // // // // //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "stats.h"

#define ASCII_ZERO 48

/**
 * @brief Manually converts a string to an int
 * 
 * @param str The string to be converted to an int
 * @return Returns the int within the string, -1 if no int was found, as all ints in this program should be >= 0
 */
int str_to_int(char *str[]) {
    int val = 0;
    for (int i = 0; i < (int)strlen(*str); i++) {
        char ch = *str[i];

        if (isdigit(ch)) {
            int ch_val = ch - ASCII_ZERO;

            val *= val + ch_val;
        } else {
            return -1;
        }
    }

    return val;
}

/**
 * @brief Main program entry point
 * 
 * @param argc length of argv
 * @param argv string elements passed to the program
 * @return int 
 */
int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "usage: review_grades score1 [score2 ...]\nnote: ignore negative score values.\n");
        return EXIT_FAILURE;
    }

    int input_population = argc - 1;
    int adjusted_population = input_population;
    printf("input population: %d\n", input_population);

    int total = 0;
    int scores[100];

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
    printf("std deviation: %f\n", std_dev(total, scores, mean));
    histogram(total, scores);

    return EXIT_SUCCESS;
}
