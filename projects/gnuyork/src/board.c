#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"

Board *board_create(FILE *input) {
    int default_size = 20;

    Board *board = (Board *)malloc(sizeof(Board));
    board->arr = (Vertex *)malloc(sizeof(Vertex) * default_size);
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

        Vertex vert = {chr, 0};
        board->arr[board->indexes] = vert;
        board->indexes++;

        if (board->indexes == board->size - 1) {
            Vertex *arr = (Vertex *)realloc(board->arr, board->size * 2);
            board->size *= 2;
            board->arr = arr;
        }
    }

    return board;
}

/// converts a 2d pair of ints to a 1d int
int linearized_2d_cords(int r, int c, int cols) {
    return (cols * c) + r;
}

char board_get(Board *board, int r, int c) {
    int index = linearized_2d_cords(r, c, board->columns);
    return board->arr[index].val;
}

void board_put(Board *board, int r, int c, char chr) {
    int index = linearized_2d_cords(r, c, board->columns);
    board->arr[index].val = chr;
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
        if (i % board->columns == 0 && i != 0) {
            printf("|");
        } else if (i == 0) {
            printf(" ");
        }
        char point = board->arr[i].val;
        if (point == '0') {
            point = '.';
        } else if (point == '1') {
            point = '#';
        } else if (point == '2') {
            point = '+';
        }
        printf(" %c", point);
        if (i % board->columns == board->columns - 1 && i != board->indexes-1) {
            printf(" |\n");
        } else if (i == board->indexes - 1) {
            printf(" \n");
        }
    }
    print_details(board->indexes / board->columns);
}
