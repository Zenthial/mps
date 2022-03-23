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
        int current_point_index = linearized_2d_cords(currentPoint->x, currentPoint->y, board->row_elms);
        QueueADT neighbors = board_get_neighbors(board, currentPoint->x, currentPoint->y);
        // printf("x: %d, y: %d neighbors size: %d\n", currentPoint->x, currentPoint->y, que_size(neighbors));

        while (!que_empty(neighbors)) {
            Point *neighbor = (Point *)que_remove(neighbors);
            int index = linearized_2d_cords(neighbor->x, neighbor->y, board->row_elms);
            if (visited[index] != 1) {
                // printf("visited index %d, value %d, neighbor x: %d, neighbor y: %d\n", index, visited[index], neighbor->x, neighbor->y);
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
                // printf("x %d, y %d has been visited\n", neighbor->x, neighbor->y);
                free(neighbor);
            }

        }
    }

    int steps = 0;
    // printf("0 0 %d\n", back_trace[0]);
    while (back_trace[found_index] != -1 && found_index != -1) {
        board_set_path(board, found_index);
        // printf("trace index: %d\n", back_trace[found_index]);
        found_index = back_trace[found_index];
        steps++;
    }
    if (steps > 0) {
        board_set_path(board, 0);
    }

    while(!que_empty(queue)) {
        Point *to_free = (Point *)que_remove(queue);
        free(to_free);
    }

    free(visited);

    return steps;
}

int main(int argc, char *argv[]) {
    Board *board = board_create(stdin);
    const Point start = {0, 0};
    const Point end = {(board->indexes/board->columns) - 1, board->columns - 1};
    // printf("start: %d end: %d", end.x, end.y);
    // printf("elms %d\n", board->indexes);
    board_print(board);
    int steps = bfs(board, start, end);

    if (steps > 0) {
        printf("Solution in %d steps.\n", steps+1);
    } else {
        printf("No solution.\n");
    }
    board_print(board);
    board_delete(board);

    return 0;
}
