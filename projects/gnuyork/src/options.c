#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "options.h"

bool get_options(
    bool *help, bool *pretty_print_solution, bool *solution_print,
    bool *pretty_print_initial, FILE **in_file_pointer, FILE **out_file_pointer,
    int argc, char *argv[]
) {
    bool return_val = true;
    char c;
    while ((c = getopt(argc, argv, "hdspi:o:")) != -1) {
        switch(c) {
            case 'h':
                *help = true;
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
                *in_file_pointer = fopen(optarg, 'r');
                break;
            case 'o':
                *out_file_pointer = fopen(optarg, 'r');
                break;
            default:
                break;
        }
    }

    return return_val;
}