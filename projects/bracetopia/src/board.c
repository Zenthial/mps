/// board.c
/// handles all things related to the board state
/// author: tom schollenberger

#include <stdio.h>
#include <stdlib.h>

#include "board.h"

void fill_board(int size, char **board, int amount, char fill_char) {
    for (int i = 0; i < amount; i++) {
        int row = rand();
        row %= size;
        int col = rand();
        col %= size;
        if (board[row][col] == '.') {
            board[row][col] = fill_char;
        } else {
            i--;
        }
    }
}

char** create_board(int dimension, int end_num, int new_num) {
    // int size = dimension * dimension;
    // printf("%d\n", size);
    char **board = (char **) malloc(dimension * sizeof (char *));
    
    for (int i = 0; i < dimension; i++) {
        board[i] = (char *) malloc(dimension * sizeof (char));
    }

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            board[i][j] = '.';
        }
    }

    fill_board(dimension, board, end_num, 'e');
    fill_board(dimension, board, new_num, 'n');
    print_board(dimension, board);

    return board;
}

void print_board(int size, char **board) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}