#include <stdio.h>
#include <stdint.h>

#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct vertex {
    char val;
    int8_t visited;
} Vertex;

typedef struct board{
    Vertex *arr;
    int size;
    int indexes;
    int columns;

} Board;

Board *board_create(FILE *input);

char board_get(Board *board, int r, int c);

void board_put(Board *board, int r, int c, char chr);

void board_delete(Board *board);

void board_print(Board *board);

/// takes in a row and a column and coverts it to a singular int
/// maps a 2d coord to a 1d index
/// @param r the int of the row to look at
/// @param c the int of the column to look at
/// @param cols the total columns within the board
int linearized_2d_cords(int r, int c, int cols);

#endif // !_BOARD_H_
