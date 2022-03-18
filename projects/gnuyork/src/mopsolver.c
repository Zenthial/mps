#include <stdio.h>
#include "board.h"

int main() {
    Board *board = board_create(stdin);
    board_print(board);
    board_delete(board);

    return 0;
}