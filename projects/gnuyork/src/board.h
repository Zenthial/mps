#include <stdio.h>

#include "QueueADT.h"

#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct point {
    int x;
    int y;
} Point;

typedef struct board{
    char *arr;
    int size;
    int indexes;
    int columns;
    int row_elms;
} Board;

/**
 * @brief Creates the board represtation structure
 * 
 * @param input The File to read input from
 * @return Board* 
 */
Board *board_create(FILE *input);

/**
 * @brief Gets a char on the board
 * 
 * @param board The board struct pointer
 * @param r The row
 * @param c The column
 * @return char The char at that specific position
 */
char board_get(Board *board, int r, int c);

/**
 * @brief Puts a character at a specific position on a board
 * 
 * @param board The board pointer
 * @param r The row
 * @param c The column
 * @param chr The char that should be put
 */
void board_put(Board *board, int r, int c, char chr);

/**
 * @brief Changes a char at a point to the path symbol
 * 
 * @param board The board pointer
 * @param index The index to set the path at
 */
void board_set_path(Board *board, int index);

/**
 * @brief Cleans up a board pointer
 * 
 * @param board The board pointer
 */
void board_delete(Board *board);

/**
 * @brief Prints out the board
 * 
 * @param board The board pointer
 * @param out_stream The file to write out to
 */
void board_print(Board *board, FILE *out_stream);

/// takes in a row and a column and coverts it to a singular int
/// maps a 2d coord to a 1d index
/// @param r the int of the row to look at
/// @param c the int of the column to look at
/// @param cols the total columns within the board
int linearized_2d_cords(int r, int c, int num_row_elms);

/**
 * @brief Gets the neighbors of a given pint
 * 
 * @param board The board pointer
 * @param r The row
 * @param c The column
 * @return QueueADT A queue holding all of the neighbors
 */
QueueADT board_get_neighbors(Board *board, int r, int c);

#endif // !_BOARD_H_
