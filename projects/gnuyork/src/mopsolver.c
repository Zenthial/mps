#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "QueueADT.h"
#include "board.h"
#include "options.h"
#include "solver.h"

int main(int argc, char *argv[]) {
    bool pretty_print_solution = false;
    bool solution_print = false;
    bool pretty_print_initial = false;
    FILE *in_file_pointer = stdin;
    FILE *out_file_pointer = stdout;

    get_options(&pretty_print_solution, &solution_print, 
                &pretty_print_initial, &in_file_pointer, &out_file_pointer, argc, argv);

    Board *board = board_create(in_file_pointer);
    Point *start = (Point *)malloc(sizeof(Point));
    start->x = 0;
    start->y = 0;
    const Point end = {(board->indexes / board->columns) - 1, board->columns - 1};

    if (pretty_print_initial) {
        board_print(board, out_file_pointer);
    }

    int steps = solve(board, start, end);
    if (solution_print) {
        if (steps > 0) {
            fprintf(out_file_pointer, "Solution in %d steps.\n", steps + 1);
        } else {
            fprintf(out_file_pointer, "No solution.\n");
        }
    }
    
    if (pretty_print_solution) {
        board_print(board, out_file_pointer);
    }
    
    board_delete(board);

    if (in_file_pointer != stdin) {
        fclose(in_file_pointer);
    }

    if (out_file_pointer != stdout) {
        fclose(out_file_pointer);
    }

    return 0;
}
