#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define _BOARD_INCLUDE_
typedef struct board {
    char *arr;
    int size;
    int indexes;
    int columns;

} Board;

#include "board.h"

Board *board_create(FILE *input) {
    int default_size = 20;

    Board *board = (Board *)malloc(sizeof(Board));
    board->arr = (char *)malloc(sizeof(char) * default_size);
    board->size = default_size;
    board->indexes = 0;
    board->columns = 0;

    while (true) {
        char chr = fgetc(input);

        if (feof(input))
            break;

        if (chr == ' ')
            continue;

        if (chr == '\n') {
            board->columns++;
            continue;
        }

        board->arr[board->indexes] = chr;
        board->indexes++;

        if (board->indexes == board->size - 1) {
            char *arr = (char *)realloc(board->arr, board->size * 2);
            board->size *= 2;
            board->arr = arr;
        }
    }

    return board;
}

/// takes in a row and a column and coverts it to a singular int
/// maps a 2d coord to a 1d index
/// @param r the int of the row to look at
/// @param c the int of the column to look at
/// @param cols the total columns within the board
int linearized_2d_cords(int r, int c, int cols) {
    return (cols * c) + r;
}

char board_get(Board *board, int r, int c) {
    int index = linearized_2d_cords(r, c, board->columns);
    return board->arr[index];
}

void board_put(Board *board, int r, int c, char chr) {
    int index = linearized_2d_cords(r, c, board->columns);
    board->arr[index] = chr;
}

void board_delete(Board *board) {
    free(board->arr);
    free(board);
}

/// prints out the top and bottom |----| lines
/// @param row_size how many - chars should be written
void print_details(int row_size) {
    printf("|");
    for (int i = 0; i < row_size; i++) {
        printf(" -");
    }
    printf(" |\n");
}

void board_print(Board *board) {
    print_details(board->indexes / board->columns);
    for (int i = 0; i < board->indexes; i++) {
        if (i == 0 || i % board->columns == 0) {
            printf("|");
        }
        printf(" %c", board->arr[i]);
        if (i % board->columns == board->columns - 1) {
            printf(" |\n");
        }
    }
    print_details(board->indexes / board->columns);
}