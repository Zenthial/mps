/**
 * @file options.h
 * @author Tom Schollenberger
 * @brief Handles all command line options parsing
 * 
 */


#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Get the options by filling the respective pointers
 * 
 * @param pretty_print_solution Pretty print bool to print the final state
 * @param solution_print Print the solution
 * @param pretty_print_initial Pretty print bool to print the initial board state
 * @param in_file_pointer Pointer to the instream
 * @param out_file_pointer Pointer to the outstream
 * @param argc Num of arguments in argv
 * @param argv String array of arguments
 */
void get_options(bool *pretty_print_solution, bool *solution_print, 
    bool *pretty_print_initial, FILE **in_file_pointer, FILE **out_file_pointer,
    int argc, char *argv[]);
