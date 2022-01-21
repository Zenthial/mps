#include "math.h"
#include "stdio.h"

double average( int count, const int scores[] ) {
    double val = 0;

    for (int i = 0; i < count; i++) {
        val += scores[i];
    }

    return val / count;
}

/// TODO write full docstring including @param and @return for std_dev function

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

int find_grade(int grade, int limits[]) {
    for (int i = 0; i < 10; i++) {
        int limit = limits[i];
        if (grade >= limit) {
            return i;
        }
    }

    return -1;
}

/// TODO write full docstring including @param and @return for histogram

void histogram( int count, const int scores[] ) {
    int grade_limits[] = {92, 89, 85, 82, 79, 75, 72, 69, 60, 0};
    char grade_chars[10][4] = {"A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"};

    int grades[10];

    for (int i = 0; i < 10; i++) {
        grades[i] = 0;
    }

    for (int i = 0; i < count; i++) {
        int grade_index = find_grade(scores[i], grade_limits);
        grades[grade_index] += 1;
    }

    for (int i = 0; i < 10; i++) {
        int grade_num = grades[i];

        printf("%s:\t%d\n", grade_chars[i], grade_num);
    }
}