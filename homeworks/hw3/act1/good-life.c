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


	void header(void)
   {
	  printf("\n\t..Welcome to the Game of life..\n");
   }
	
	void survivalRule(char life[][20], int x, int y)
   {
	  int row, col;
	  int neighbors = 0;
	  for(row = 1; row<19; row++)
	  {
		 for(col = 1; col<19; col++)
		 {
			if( life[row][col] == '*') // fix1, convert str to char
			
			   if(life[row - 1][col - 1] == '*')
				  ++neighbors;
			   if(life[row - 1][col] == '*')
				  ++neighbors;
			   if(life[row - 1][col + 1] == '*')
				  ++neighbors;
			   if(life[row][col - 1] == '*')
				  ++neighbors;
			   if(life[row][col + 1] == '*')
				  ++neighbors;
			   if(life[row + 1][col - 1] == '*')
				  ++neighbors;
			   if(life[row + 1][col] == '*')
				  ++neighbors;
			   if(life[row + 1][col + 1] == '*')
				  ++neighbors;
			   if(neighbors == 2 || neighbors == 3)
			   {
				  life[row][col] == '*';
			   }
			}
		 }
	  }
	  return;
   }
	
	void birthRule(char life[][20], int x, int y)
   {
	  int row, col;
	  int neighbors = 0;
	  for(row = 1; row<19; row++)
	  {
		 for(col = 1; col<19; col++)
		 {
			if( life[row][col]== '*')
			{
			   if(life[row - 1][col - 1] == '*')
				  neighbors++;
			   if(life[row - 1][col] == '*')
				  neighbors++;
			   if(life[row - 1][col + 1] == '*')
				  neighbors++;
			   if(life[row][col - 1] == '*')
				  neighbors++;
			   if(life[row][col + 1] == '*')
				  neighbors++;
			   if(life[row + 1][col - 1] == '*')
				  neighbors++;
			   if(life[row + 1][col] == '*')
				  neighbors++;
			   if(life[row + 1][col + 1] = '*')
				  neighbors++;
			   if(neighbors == 3)
			   {
			   	life[row][col] == '*';
			   }
			}
		 }
	  }

	  return;
   }
	
	void deathRule(char life[][20], int x, int y)
   {
	  int row, col;
	  int neighbors = 0;
	  for(row = 1; row<19; row++)
	  {
		 for(col = 1; col<19; col++)
		 {
			if( life[row][col] == '*')
			{
			   if(life[row - 1][col - 1] == '*')
				  neighbors++;
			   if(life[row - 1][col] == '*')
				  neighbors++;
			   if(life[row - 1][col + 1] == '*')
				  neighbors++;
			   if(life[row][col - 1] == '*')
				  neighbors++;
			   if(life[row][col + 1] == '*')
				  neighbors++;
			   if(life[row + 1][col - 1] == '*')
				  neighbors++;
			   if(life[row + 1][col] == '*')
				  neighbors++;
			   if(life[row + 1][col + 1] = '*')
				  neighbors++;
			   if(neighbors < 2 || neighbors > 4)
			   {
				  life[row][col] == ' ';
			   }
			}
		 }
	  }
	  return;
   }

   	
int main(void)
   {
	  int orgs, gens;
	  int i, a, b, row, col;
	  int count = 0;
	  int x = 19;
	  int y = 19;
	  char ans;
	  int numrows;
	  int numcols;
	  char life[20][20];
   	
	  header();

		 printf("\nPlease enter the initial number of organisms: ");
		 scanf("%i", &orgs);
	  
	// start curses environment and find boundaries of window
	initscr();                            // Start curses mode 
	getmaxyx( stdscr, numrows, numcols);  // this is a MACRO; no & needed

		 srand( 31 );
			  
		 for(i = 0; i<orgs; i++)
		 {
			row = rand();
			row %= 20;
			col = rand();
			col %= 20;
			life[row][col] == '*';
		 }
		 
		 for(row = 0; row<20; row++)
		 {
			for(col = 0; col<20; col++)
			{
			   if(life[row][col] != '*')
			   		life[row][col] == ' ';
			}
		 }
			  
		 while ( 1 ) {
			move( 0, 0);
			for(row = 0; row<20; row++)
		 	{
				  for(col = 0; col<20; col++)
				  {
					  printw("%c", life[row][col]); // fix 2, convert %s to %c to stop the seg fault
				  }
				  printw( "\n");
		 	}
			move( 20, 0);
			refresh();
		  printw("generation: %d\n", count);
			count++;
			birthRule(life, x, y);
			survivalRule(life, x, y);
			deathRule(life, x, y);
		 }
		  
	endwin(); // End curses mode at the end of the program
	  return 0;

   }

