#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "options.h"

#define SPCE "          "

void print_help() {
    printf("Usage:\n");
    printf("mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n");
    printf("Options:\n");
    printf("  -h%sPrint usage and options list to stdout only.    (Default: off)\n", SPCE);
    printf("  -d%sPretty-print (display) the maze after reading.  (Default: off)\n", SPCE);
    printf("  -s%sPrint length of shortest path or 'No solution'. (Default: off)\n", SPCE);
    printf("  -p%sPretty-print maze with the path, if one exists. (Default: off)\n", SPCE);
    printf("  -i infile   Read maze from infile.                          (Default: stdin)\n");
    printf("  -o outfile  Write all output to outfile.                    (Default: stdout)\n");
}

bool get_options(
    bool *pretty_print_solution, bool *solution_print,
    bool *pretty_print_initial, FILE **in_file_pointer, FILE **out_file_pointer,
    int argc, char *argv[]
) {
    bool return_val = true;
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

    return return_val;
}
