// file: solver.c
// description:
// implements both bfs and a* solving algos
// author: Tom Schollenberger

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "QueueADT.h"

typedef struct _a_star_point {
    int x;
    int y;
    int f;
    int g;
    int h;
    int index;
    struct _a_star_point *parent;
} AStarPoint;

/**
 * @brief A basic BFS algorithm implementation
 * 
 * @param board Board pointer
 * @param start Start point
 * @param end End point
 * @return int The number of moves it took to solve
 */
int bfs(Board *board, Point *start, Point end) {
    QueueADT queue = que_create(NULL);
    int *visited = (int *)calloc(board->size, sizeof(int));
    int *back_trace = (int *)malloc(board->size * sizeof(int));
    for (int i = 0; i < board->size; i++) {
        back_trace[i] = -1;
    }
    bool found = false;
    int found_index = -1;

    que_insert(queue, start);
    visited[0] = 1;
    
    if (board_get(board, start->x, start->y) == '0') {
        while (!que_empty(queue) && !found) {
            Point *currentPoint = (Point *)que_remove(queue);
            int current_point_index = linearized_2d_cords(currentPoint->x, currentPoint->y, board->row_elms);
            QueueADT neighbors = board_get_neighbors(board, currentPoint->x, currentPoint->y);
            // printf("x: %d, y: %d neighbors size: %d\n", currentPoint->x, currentPoint->y, que_size(neighbors));

            while (!que_empty(neighbors)) {
                Point *neighbor = (Point *)que_remove(neighbors);
                if (found) {
                    free(neighbor);
                    continue;
                }
                int index = linearized_2d_cords(neighbor->x, neighbor->y, board->row_elms);
                if (visited[index] != 1) {
                    // printf("visited index %d, value %d, neighbor x: %d, neighbor y: %d\n", index, visited[index], neighbor->x, neighbor->y);
                    visited[index] = 1;
                    back_trace[index] = current_point_index;
                    if (neighbor->x == end.x && neighbor->y == end.y) {
                        found = true;
                        found_index = index;
                        free(neighbor);
                        continue;
                    }
                    que_insert(queue, neighbor);
                } else {
                    // printf("x %d, y %d has been visited\n", neighbor->x, neighbor->y);
                    free(neighbor);
                }

            }
            free(neighbors);
            free(currentPoint);
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
    free(back_trace);
    free(queue);

    return steps;
}

/// wrapper method for testing different solution algs
int solve(Board *board, Point *start, Point end) {
    return bfs(board, start, end);
}
