// file: solver.h
// description:
// abstracts away the method we use to solve the board
// allows the developer to switch between solving methods (bfs vs a*)
// author: Tom Schollenberger

#include "board.h"

/**
 * @brief Solves a board
 * 
 * @param board Board pointer
 * @param start Start point
 * @param end End point
 * @return int 
 */
int solve(Board *board, Point *start, Point end);
