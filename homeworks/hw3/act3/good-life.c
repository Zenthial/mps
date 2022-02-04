/// good-life.c
///
/// This is derived from faulty code downloaded by copy-paste in BOARD_SIZE15, and 
/// modified to use curses for screen display.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; the mix of TAB and spaces indentation
/// needs correction, and spacing between tokens is inconsistent.
/// The course style puts the '{' at the end of the function header, not
/// on a line of its own, and function headers belong at the left margin.
/// </li>
/// <li>  documentation is almost non-existent.
/// </li>
/// <li>  proper, public C documentation uses /// or /** ... */ format comments.
/// </li>
/// </ol>
///

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ncurses.h>
//
// curses programs need to link with the -lcurses flag 
// For manual pages, run 'man curses' and
// also see https://github.com/tony/NCURSES-Programming-HOWTO-examples/
//

#define BOARD_SIZE 20 /// Constant definition for the size of the board. The board is square, so this applies for both rows and columns

/*
 * Prints out the welcome message
*/
void header(void) {
	printf("\n\t..Welcome to the Game of life..\n");
}

/**
 * Gets the number of neighbors surrounding a given cell
 * 
 * @param row the int of the row
 * @param col the int of the column
 * @param board_size The int size of the board
 * @param life The char array representing the game of life board
 * @return The number of neighbors surrounding the cell
*/
int get_neighbors(int row, int col, int board_size, char life[][board_size]) {
	int neighbors = 0;

	int col_minus = (col - 1 >= 0) ? col - 1 : board_size;
	int row_minus = (row - 1 >= 0) ? row - 1 : board_size;
	int col_plus = (col + 1 < board_size) ? col + 1 : 0;
	int row_plus = (row + 1 < board_size) ? row + 1 : 0;

	if (life[row_minus][col_minus] == '*') ++neighbors;
	if (life[row_minus][col] == '*') ++neighbors;
	if (life[row_minus][col_plus] == '*') ++neighbors;
	if (life[row][col_minus] == '*') ++neighbors;
	if (life[row][col_plus] == '*') ++neighbors;
	if (life[row_plus][col_minus] == '*') ++neighbors;
	if (life[row_plus][col] == '*') ++neighbors;
	if (life[row_plus][col_plus] == '*') ++neighbors;

	return neighbors;
}

/**
 * Handles the survival rule of the game of life
 * 
 * @param board_size The int size of the board
 * @param life The char array representing the game of life board
*/
void do_rules(int board_size, char life[][board_size]) {
	char new_life[board_size][board_size];

	for (int row = 0; row < board_size; row++) {
		for (int col = 0; col < board_size; col++) {
			int neighbors = get_neighbors(row, col, board_size, life);
			char current_cell = life[row][col];

			// Any live cell with fewer than two live neighbors dies, as if by underpopulation.
			if (neighbors < 2) {
				new_life[row][col] = ' ';
			// Any live cell with two or three live neighbors lives on to the next generation.
			} else if (current_cell == '*' && (neighbors == 2 || neighbors == 3)) {
				new_life[row][col] = '*';
			// Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
			} else if (current_cell == ' ' && neighbors == 3) {
				new_life[row][col] = '*';
			// Any live cell with more than three live neighbors dies, as if by overpopulation.
			} else if (neighbors > 3) {
				new_life[row][col] = ' ';
			} else {
				new_life[row][col] = life[row][col];
			}
		}
	}

	for (int row = 0; row < board_size; row++) {
		for (int col = 0; col < board_size; col++) {
			life[row][col] = new_life[row][col];
		}
	}
}

/**
 *	Main entry point of the program, reads no command line args 
 * 	@return EXIT_SUCCESS of 0
*/
int main(void) {
	int orgs;
	int count = 0;
	// fix 6, remove a bunch of unused variables
	int numrows;
	int numcols;
	char life[BOARD_SIZE][BOARD_SIZE];

	header();

	printf("\nPlease enter the initial number of organisms: ");
	scanf("%i", &orgs);

	// start curses environment and find boundaries of window
	initscr();                            // Start curses mode 
	getmaxyx(stdscr, numrows, numcols);  // this is a MACRO; no & needed
	mvprintw(numrows - 1, numcols / 4, "screen is %d wide by %d high\n", 
		numcols, numrows);
	refresh(); // fix 6, actually use numrows and numcols

	srand(31);

	for (int i = 0; i < orgs; i++) {
		int row = rand();
		row %= BOARD_SIZE;
		int col = rand();
		col %= BOARD_SIZE;
		life[row][col] = '*'; // fix 3, convert == to =
	}

	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			if (life[row][col] != '*') life[row][col] = ' '; // fix 3, convert == to =
		}
	}

	while ( 1 ) {
		usleep(820225L);
		move(0, 0);
		for (int row = 0; row < BOARD_SIZE; row++) {
			for (int col = 0; col < BOARD_SIZE; col++) {
				printw("%c", life[row][col]); // fix 2, change %s to %c, not sure why that causes a segfault
			}
			printw("\n");
		}
		move(BOARD_SIZE, 0);
		refresh();
		printw("generation: %d\n", count);
		count++;
		// fix 5, applies to all 3 below, remove x and y passing
		// birthRule(BOARD_SIZE, life);
		// survivalRule(BOARD_SIZE, life);
		// deathRule(BOARD_SIZE, life);
		do_rules(BOARD_SIZE, life);
	}

	endwin(); // End curses mode at the end of the program
	return 0;
}
