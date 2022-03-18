#include <stdio.h>

#ifndef _BOARD_H_
#define _BOARD_H_

#ifndef _BOARD_INCLUDE_
#define _BOARD_INCLUDE_

typedef struct board_ Board;

#endif // !_BOARD_INCLUDE_

Board *board_create(FILE *input);

char board_get(Board *board, int r, int c);

void board_put(Board *board, int r, int c, char chr);

void board_delete(Board *board);

void board_print(Board *board);

#endif // !_BOARD_H_