// file: solver.h
// description:
// abstracts away the method we use to solve the board
// allows the developer to switch between solving methods (bfs vs a*)
// author: Tom Schollenberger

#include "board.h"

int solve(Board *board, Point *start, Point end);
