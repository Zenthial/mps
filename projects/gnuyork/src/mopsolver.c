#include <stdio.h>
#include "board.h"

int main() {
    Board *board = board_create(stdin);
    board_print(board);

    printf("%c", board_get(board, 0, 0));
    printf("%c", board_get(board, 1, 0));
    printf("%c", board_get(board, 1, 1));

    board_delete(board);

    return 0;
}