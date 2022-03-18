#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "QueueADT.h"

Board *board_create(FILE *input) {
    int default_size = 20;

    Board *board = (Board *)malloc(sizeof(Board));
    board->arr = (char *)malloc(sizeof(char) * default_size);
    board->size = default_size;
    board->indexes = 0;
    board->columns = 0;

    while (true) {
        char chr = fgetc(input);

        if (feof(input))
            break;

        if (chr == ' ')
            continue;

        if (chr == '\n') {
            board->columns++;
            continue;
        }

        board->arr[board->indexes] = chr;
        board->indexes++;

        if (board->indexes == board->size - 1) {
            char *arr = (char *)realloc(board->arr, board->size * 2);
            board->size *= 2;
            board->arr = arr;
        }
    }

    return board;
}

QueueADT board_get_neighbors(Board *board, int r, int c) {
    int possible_neighbors[8][2] = {
        {r + 1, c}, {r - 1, c}, {r - 1, c - 1}, {r + 1, c + 1},
        {r + 1, c - 1}, {r - 1, c + 1}, {r, c - 1}, {r, c + 1}
    };

    QueueADT neighbors_queue = que_create(NULL);

    for (int i = 0; i < 8; i++) {
        int x, y;
        x = possible_neighbors[i][0];
        y = possible_neighbors[i][1];

        int index = linearized_2d_cords(x, y, board->columns);
        if (x >= 0 && y >= 0) {
            if (board->arr[index] == '0') {
                Point *point = (Point *)malloc(sizeof(Point));
                point->x = x;
                point->y = y;
                printf("inserted from x: %d, y: %d\n", x, y);
                que_insert(neighbors_queue, point);
            }
        }
        
    }

    return neighbors_queue;
}

/// converts a 2d pair of ints to a 1d int
int linearized_2d_cords(int r, int c, int cols) {
    return (cols * c) + r;
}

char board_get(Board *board, int r, int c) {
    int index = linearized_2d_cords(r, c, board->columns);
    return board->arr[index];
}

void board_put(Board *board, int r, int c, char chr) {
    int index = linearized_2d_cords(r, c, board->columns);
    board->arr[index] = chr;
}

void board_set_path(Board *board, int index) {
    board->arr[index] = '2';
}

void board_delete(Board *board) {
    free(board->arr);
    free(board);
}

/// prints out the top and bottom |----| lines
/// @param row_size how many - chars should be written
void print_details(int row_size) {
    printf("|");
    for (int i = 0; i < row_size; i++) {
        printf(" -");
    }
    printf(" |\n");
}

void board_print(Board *board) {
    int rows = board->indexes / board->columns;
    int row_counter = 0;
    print_details(rows);
    for (int i = 0; i < board->indexes; i++) {
        if (i == 0) {
            printf(" ");
        } else if (row_counter == 0) {
            printf("|");
        }

        char point = board->arr[i];
        if (point == '0') {
            point = '.';
        } else if (point == '1') {
            point = '#';
        } else if (point == '2') {
            point = '+';
        }
        printf(" %c", point);

        if (i == board->indexes - 1) {
            printf(" \n");
        } else if (row_counter == rows - 1) {
            printf(" |\n");
        }

        row_counter++;
        if (row_counter >= rows) {
            row_counter = 0;
        }
    }
    print_details(rows);
}
