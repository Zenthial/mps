#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "QueueADT.h"

int bfs(Board *board, Point start, Point end) {
    QueueADT queue = que_create(NULL);
    int *visited = (int *)calloc(board->size, sizeof(int));
    int *back_trace = (int *)malloc(board->size * sizeof(int));
    for (int i = 0; i < board->size; i++) {
        back_trace[i] = -1;
    }
    bool found = false;
    int found_index = -1;

    que_insert(queue, &start);
    visited[0] = 1;
    while (!que_empty(queue) && !found) {
        Point *currentPoint = (Point *)que_remove(queue);
        int current_point_index = linearized_2d_cords(currentPoint->x, currentPoint->y, board->columns);
        QueueADT neighbors = board_get_neighbors(board, currentPoint->x, currentPoint->y);
        printf("neighbors size: %d\n", que_size(neighbors));

        while (!que_empty(neighbors)) {
            Point *neighbor = (Point *)que_remove(neighbors);
            int index = linearized_2d_cords(neighbor->x, neighbor->y, board->columns);
            if (visited[index] != 1) {
                printf("visited index %d, value %d, neighbor x: %d, neighbor y: %d\n", index, visited[index], neighbor->x, neighbor->y);
                visited[index] = 1;
                back_trace[index] = current_point_index;
                if (neighbor->x == end.x && neighbor->y == end.y) {
                    found = true;
                    found_index = index;
                    free(neighbor);
                    break;
                }
                que_insert(queue, neighbor);
            } else {
                free(neighbor);
            }

        }
    }

    int steps = 0;
    printf("0 0 %d\n", back_trace[0]);
    while (back_trace[found_index] != -1) {
        board_set_path(board, found_index);
        // printf("trace index: %d\n", back_trace[found_index]);
        found_index = back_trace[found_index];
        steps++;
    }
    board_set_path(board, 0);

    while(!que_empty(queue)) {
        Point *to_free = (Point *)que_remove(queue);
        free(to_free);
    }

    free(visited);

    return steps;
}

int main() {
    Board *board = board_create(stdin);
    Point start = {0, 0};
    Point end = {(board->indexes/board->columns) - 1, board->columns - 1};
    int steps = bfs(board, start, end);

    printf("Number of steps: %d\n", steps);
    board_print(board);
    board_delete(board);

    return 0;
}
