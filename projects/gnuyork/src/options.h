#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool get_options(bool *pretty_print_solution, bool *solution_print, 
    bool *pretty_print_initial, FILE **in_file_pointer, FILE **out_file_pointer,
    int argc, char *argv[]);
