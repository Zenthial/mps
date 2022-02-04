/// bad-life.c
///
/// This is derived from faulty code downloaded by copy-paste in 2015, and 
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

#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
//
// curses programs need to link with the -lcurses flag 
// For manual pages, run 'man curses' and
// also see https://github.com/tony/NCURSES-Programming-HOWTO-examples/
//


void header(void) {
	printf("\n\t..Welcome to the Game of life..\n");
}

void survivalRule(char life[][20]) { // fix 5, remove x and y 
	int neighbors = 0;

	for (int row = 1; row < 19; row++) {
		for (int col = 1; col < 19; col++) {
			if (life[row][col] == '*') { // fix1, convert str to char
				if (life[row - 1][col - 1] == '*') ++neighbors;
				if (life[row - 1][col] == '*') ++neighbors;
				if (life[row - 1][col + 1] == '*') ++neighbors;
				if (life[row][col - 1] == '*') ++neighbors;
				if (life[row][col + 1] == '*') ++neighbors;
				if (life[row + 1][col - 1] == '*') ++neighbors;
				if (life[row + 1][col] == '*') ++neighbors;
				if (life[row + 1][col + 1] == '*') ++neighbors;
				if (neighbors == 2 || neighbors == 3) {
					life[row][col] = '*'; // fix 3, convert == to =
				}
			}
		}
	}
}

void birthRule(char life[][20]) { // fix 5, remove x and y
	int neighbors = 0;

	for (int row = 1; row < 19; row++) {
		for (int col = 1; col < 19; col++) {
			if (life[row][col]== '*') {
				if (life[row - 1][col - 1] == '*') neighbors++;
				if (life[row - 1][col] == '*') neighbors++;
				if (life[row - 1][col + 1] == '*') neighbors++;
				if (life[row][col - 1] == '*') neighbors++;
				if (life[row][col + 1] == '*') neighbors++;
				if (life[row + 1][col - 1] == '*') neighbors++;
				if (life[row + 1][col] == '*') neighbors++;
				if (life[row + 1][col + 1] == '*') neighbors++; // fix 4, change assignment to equality check 
				if (neighbors == 3) {
					life[row][col] = '*'; // fix  3, convert == to =
				}
			}
		}
	}
}

void deathRule(char life[][20]) { // fix 5, remove x and y
	int neighbors = 0;

	for (int row = 1; row < 19; row++) {
		for (int col = 1; col < 19; col++) {
			if (life[row][col] == '*') {
				if (life[row - 1][col - 1] == '*') neighbors++;
				if (life[row - 1][col] == '*') neighbors++;
				if (life[row - 1][col + 1] == '*') neighbors++;
				if (life[row][col - 1] == '*') neighbors++;
				if (life[row][col + 1] == '*') neighbors++;
				if (life[row + 1][col - 1] == '*') neighbors++;
				if (life[row + 1][col] == '*') neighbors++;
				if (life[row + 1][col + 1] == '*') neighbors++; // fix 4, change assignment to equality check
				if (neighbors < 2 || neighbors > 4) {
					life[row][col] = ' '; // fix 3, convert == to =
				}
			}
		}
	}
}

int main(void) {
	int orgs;
	int count = 0;
	// fix 6, remove a bunch of unused variables
	int numrows;
	int numcols;
	char life[20][20];

	header();

	printf("\nPlease enter the initial number of organisms: ");
	scanf("%i", &orgs);

	// start curses environment and find boundaries of window
	initscr();                            // Start curses mode 
	getmaxyx(stdscr, numrows, numcols);  // this is a MACRO; no & needed
	mvprintw(numrows - 1, numcols / 4,
		"screen is %d wide by %d high\n",
		numcols, numrows);
	refresh(); // fix 6, actually use numrows and numcols

	srand(31);

	for (int i = 0; i < orgs; i++) {
		int row = rand();
		row %= 20;
		int col = rand();
		col %= 20;
		life[row][col] = '*'; // fix 3, convert == to =
	}

	for (int row = 0; row < 20; row++) {
		for (int col = 0; col < 20; col++) {
			if (life[row][col] != '*') life[row][col] = ' '; // fix 3, convert == to =
		}
	}

	while ( 1 ) {
		move(0, 0);
		for (int row = 0; row < 20; row++) {
			for (int col = 0; col < 20; col++) {
				printw("%c", life[row][col]); // fix 2, change %s to %c, not sure why that causes a segfault
			}
			printw("\n");
		}
		move(20, 0);
		refresh();
		printw("generation: %d\n", count);
		count++;
		// fix 5, applies to all 3 below, remove x and y passing
		birthRule(life);
		survivalRule(life);
		deathRule(life);
	}

	endwin(); // End curses mode at the end of the program
	return 0;
}
