#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "QueueADT.h"

typedef struct point {
    int x;
    int y;
} Point;

void bfs(Board *board, Point start, Point end) {
    QueueADT queue = que_create(NULL);
    int *visited = (int *)malloc(sizeof(int) * board->size);
    que_insert(queue, &start);
    while (!que_empty(queue)) {
        Point *currentPoint = (Point *)que_remove(queue);
    }

    free(visited);
}

int main() {
    Board *board = board_create(stdin);
    Point start = {0, 0};
    Point end = {(board->indexes/board->columns) - 1, board->columns - 1};
    bfs(board, start, end);

    board_print(board);
    board_delete(board);

    return 0;
}
