// 
// File: stats.c
// Description: Contains all of the statistic helper functions to compute and display grades
// 
// @author tss2344: Thomas Schollenberger
// 
// // // // // // // // // // // // // // // // // // // // // // // //
#include <math.h>
#include <stdio.h>

/**
 * @brief Computes the average of a set of scores in an int array
 * 
 * @param count number of scores in the scores array
 * @param scores int array containing the scores to be averaged
 * @return double
 */
double average( int count, const int scores[] ) {
    double val = 0;

    for (int i = 0; i < count; i++) {
        val += scores[i];
    }

    return val / count;
}

/**
 * @brief Computes the standard deviation of a set of scores
 * 
 * @param count number of scores in the scores array
 * @param scores int array containing the scores to generate the standard deviation of
 * @param mean the average of the scores
 * @return double 
 */
double std_dev( int count, const int scores[], double mean ) {
    double val = 0;

    for (int i = 0; i < count; i++) {
        int x = scores[i];
        val += pow((x - mean), 2);
    }

    val /= (count - 1);
    val = sqrt(val);

    return val;
}

/**
 * @brief Finds the grade index
 * 
 * @param grade an int value greater than 0
 * @param limits an array of int values representing the cutoffs of letter grades
 * @return the index of the grade cutoff
 */
int find_grade(int grade, int limits[]) {
    for (int i = 0; i < 10; i++) {
        int limit = limits[i];
        if (grade >= limit) {
            return i;
        }
    }

    return -1;
}

/**
 * @brief Outputs a visible histogram of the scores
 * 
 * @param count number of scores in the scores array
 * @param scores int array containing the scores to generate the histogram of
 */
void histogram( int count, const int scores[] ) {
    int grade_limits[] = {92, 89, 85, 82, 79, 75, 72, 69, 60, 0};
    char grade_chars[10][4] = {"A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"};

    const int grade_array_length = 10;
    int grades[10];

    for (int i = 0; i < grade_array_length; i++) {
        grades[i] = 0;
    }

    for (int i = 0; i < count; i++) {
        int grade_index = find_grade(scores[i], grade_limits);
        grades[grade_index] += 1;
    }

    for (int i = 0; i < grade_array_length; i++) {
        int grade_num = grades[i];

        printf("%s:\t%d\n", grade_chars[i], grade_num);
    }
}
