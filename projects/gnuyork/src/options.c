/**
 * @file options.c
 * @author Tom Schollenberger
 * @brief Handles all command line options parsing
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "options.h"

#define SPCE "          "

/// Function that prints out the help statement to stdout
void print_help() {
    printf("Usage:\n");
    printf("mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n");
    printf("Options:\n");
    printf("  -h          Print usage and options list to stdout only.    (Default: off)\n");
    printf("  -d          Pretty-print (display) the maze after reading.  (Default: off)\n");
    printf("  -s          Print length of shortest path or 'No solution'. (Default: off)\n");
    printf("  -p          Pretty-print maze with the path, if one exists. (Default: off)\n");
    printf("  -i infile   Read maze from infile.                          (Default: stdin)\n");
    printf("  -o outfile  Write all output to outfile.                    (Default: stdout)\n");
}

// fills the option pointers
void get_options(
    bool *pretty_print_solution, bool *solution_print,
    bool *pretty_print_initial, FILE **in_file_pointer, FILE **out_file_pointer,
    int argc, char *argv[]
) {
    char c;
    while ((c = getopt(argc, argv, "hdspi:o:")) != -1) {
        switch(c) {
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
                break;
            case 'd':
                *pretty_print_initial = true;
                break;
            case 's':
                *solution_print = true;
                break;
            case 'p':
                *pretty_print_solution = true;
                break;
            case 'i':
                *in_file_pointer = fopen(optarg, "r");
                break;
            case 'o':
                *out_file_pointer = fopen(optarg, "w");
                break;
            default:
                break;
        }
    }
}
