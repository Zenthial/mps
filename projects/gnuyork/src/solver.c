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

int calculate_h(int curr_x, int curr_y, int goal_x, int goal_y) {
    if (curr_x == goal_x && curr_y == goal_y) {
        return 0;
    } else {
        int length = goal_x - curr_x;
        int height = goal_y - curr_y;
        int distance = (length * length) + (height * height);
        return distance;
    }
}

int compare_points(const void *one, const void *two) {
    AStarPoint *point_one = (AStarPoint *)one;
    AStarPoint *point_two = (AStarPoint *)two;

    return point_one->f > point_two->f;
}

int a_star(Board *board, Point start, Point end) {
    AStarPoint start_point = {start.x, start.y, 0, 0, 0, 0, NULL};

    QueueADT open = que_create(*compare_points);

    AStarPoint **in_open = (AStarPoint **)calloc(board->indexes+1, sizeof(AStarPoint));
    int *closed = (int *)calloc(board->indexes+1, sizeof(int));

    que_insert(open, &start_point);
    while (!que_empty(open)) {
        AStarPoint *current_point = que_remove(open);
        // printf("checking point: (%d, %d)\n", current_point->x, current_point->y);
        int current_index = linearized_2d_cords(current_point->x, current_point->y, board->row_elms);
        closed[current_index] = 1;

        if (current_point->x == end.x && current_point->y == end.y) {
            int steps = 0;
            while (current_point != NULL) {
                current_index = current_point->index;
                board_set_path(board, current_index);
                current_point = current_point->parent;
                steps++;
            }
            return steps;
        }

        QueueADT neighbors = board_get_neighbors(board, current_point->x, current_point->y);
        // printf("in neighbors loop\n");
        while(!que_empty(neighbors)) {
            Point *neighbor_point = (Point *)que_remove(neighbors);
            int point_index = linearized_2d_cords(neighbor_point->x, neighbor_point->y, board->row_elms);
            if (closed[point_index] == 1) continue;

            AStarPoint *star_point = (AStarPoint *)malloc(sizeof(AStarPoint));
            star_point->x = neighbor_point->x;
            star_point->y = neighbor_point->y;
            star_point->g = current_point->g + 1;
            star_point->h = calculate_h(neighbor_point->x, neighbor_point->y, end.x, end.y);
            star_point->f = star_point->g + star_point->h;
            // printf("current point is: (%d, %d), with neighbor point: (%d, %d) f: %d\n", current_point->x, current_point->y, star_point->x, star_point->y, star_point->f);
            star_point->parent = current_point;
            star_point->index = point_index;

            if (in_open[point_index] != NULL) {
                if (in_open[point_index]->g < star_point->g) {
                    continue;
                }
            }

            que_insert(open, star_point);
            in_open[point_index] = star_point;
        }
        // printf("left neighbors loop\n");
        que_destroy(neighbors);
    }

    return 0;
}

int solve(Board *board, Point start, Point end) {
    return bfs(board, start, end);
}
