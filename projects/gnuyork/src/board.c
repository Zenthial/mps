#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "QueueADT.h"

#define RED "\033[0;31m"
#define WHT "\033[0;37m"

Board *board_create(FILE *input) {
    int default_size = 5000;
    int num_elm_rows = 0;

    Board *board = (Board *)malloc(sizeof(Board));
    board->arr = (char *)malloc(sizeof(char) * default_size);
    board->size = default_size;
    board->indexes = 0;
    board->columns = 0;
    board->row_elms = 0;

    while (true) {
        char chr = fgetc(input);

        if (feof(input))
            break;

        if (chr == ' ')
            continue;

        if (chr == '\n') {
            board->columns++;
            board->row_elms = num_elm_rows;
            num_elm_rows = 0;
            continue;
        }

        board->arr[board->indexes] = chr;
        board->indexes++;
        num_elm_rows++;

        if (board->indexes == board->size - 1) {
            char *arr = (char *)realloc(board->arr, board->size * 2);
            board->size *= 2;
            board->arr = arr;
        }
    }

    return board;
}

QueueADT board_get_neighbors(Board *board, int r, int c) {
    int possible_neighbors[4][2] = {
        {r, c - 1}, {r, c + 1},
        {r + 1, c}, {r - 1, c},
    };

    QueueADT neighbors_queue = que_create(NULL);
    // printf("%d %d\n", r, c);

    for (int i = 0; i < 4; i++) {
        int x = possible_neighbors[i][0];
        int y = possible_neighbors[i][1];

        int index = linearized_2d_cords(x, y, board->row_elms);
        // printf("x: %d y: %d bool: %d index: %c\n", x, y, (x >= 0 && y >= 0 && y < board->row_elms && x < board->columns), board->arr[index]);

        if (x >= 0 && y >= 0 && y < board->columns && x < board->row_elms) {
            if (board->arr[index] == '0') {
                Point point = {x, y};
                printf("inserted from x: %d, y: %d\n", x, y);
                que_insert(neighbors_queue, &point);
            }
        }
    }

    return neighbors_queue;
}

/// converts a 2d pair of ints to a 1d int
int linearized_2d_cords(int r, int c, int num_row_elms) {
    return (num_row_elms * c) + r;
}

char board_get(Board *board, int r, int c) {
    int index = linearized_2d_cords(r, c, board->row_elms);
    return board->arr[index];
}

void board_put(Board *board, int r, int c, char chr) {
    int index = linearized_2d_cords(r, c, board->row_elms);
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
void print_details(int row_size, FILE *out_stream) {
    fprintf(out_stream, "|-");
    for (int i = 0; i < row_size; i++) {
        fprintf(out_stream, "--");
    }
    fprintf(out_stream, "|\n");
}

void board_print(Board *board, FILE *out_stream) {
    int rows = board->indexes / board->columns;
    int row_counter = 0;
    print_details(rows, out_stream);
    for (int i = 0; i < board->indexes; i++) {
        if (i == 0) {
            fprintf(out_stream, "  ");
        } else if (row_counter == 0) {
            fprintf(out_stream, "| ");
        }

        char point = board->arr[i];
        if (point == '0') {
            point = '.';
        } else if (point == '1') {
            point = '#';
        } else if (point == '2') {
            point = '+';
        }

        if (point == '+') {
            fprintf(out_stream, "%s%c%s ", RED, point, WHT);
        } else {
            fprintf(out_stream, "%c ", point);
        }

        // fprintf(out_stream, "%c ", point);

        if (i == board->indexes - 1) {
            fprintf(out_stream, " \n");
        } else if (row_counter == rows - 1) {
            fprintf(out_stream, "|\n");
        }

        row_counter++;
        if (row_counter >= rows) {
            row_counter = 0;
        }
    }
    print_details(rows, out_stream);
}
