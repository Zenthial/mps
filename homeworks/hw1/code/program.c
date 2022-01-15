//
// File: program.c
// program.c is an example of a documented file.
// The file also offers TODO notes of advice; delete or replace these.
// @author TODO_AUTHOR_FULL_NAME_
// // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>

/* TODO_ remove this instruction comment block after reading.
 * C function docstrings appear before the function declaration.
 * Function documentation 'docstrings' must be publishable, and
 * the format of the comment block determines publishability.
 *
 * This comment block is NOT publishable and neither is the file header.
 * Javadoc style comments or C# style 'triple-quotes' are publishable.
 *
 * The docstring should document its input parameters and return values.
 */

/// TODO_ provide function purpose documentation -- its 'docstring'
/// TODO_ if main has no args, change to "main( void )" and remove param lines
/// @param argc  number of command line arguments, including program name
/// @param argv  supplied command line arguments, including program name
/// @returns error_code  EXIT_SUCCESS if no error or EXIT_FAILURE

int main( int argc, char* argv[] ) {

    // TODO_ indentation should be at least 3 spaces; 2 is not enough.

    // TODO_ wrap code lines when they get 'too long' (~80 chars).
    printf( "The argument count of load module %s is %d.\n",
            argv[0], argc );

    return EXIT_SUCCESS ;
}

