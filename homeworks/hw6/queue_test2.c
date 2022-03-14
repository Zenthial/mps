// file: queue_test2.c
//
// Description:  test driver for the QueueADT module provided to students
//
// This test program creates three queues (one an ascending-ordered
// queue, one a descending-ordered queue, and one a FIFO queue),
// inserts a number of character items into it, and then removes and
// prints them.
//
// Author:  wrc
// Author:  CS@RIT.EDU

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "QueueADT.h"

//
// Sequence of test values to be inserted and removed
//

static char testData[] = { 'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 'f', 'u', 'n' };
static int numData = sizeof(testData) / sizeof(char);

//
// Comparison function for characters sorted in ascending order
//

static int cmp_int64_ascend( const void *a, const void *b ) {
	char ca = (char) (long int) a;
	char cb = (char) (long int) b;

	return( ca - cb );
}

//
// Comparison function for characters sorted in descending order
//

static int cmp_int64_descend( const void *a, const void *b ) {
	char ca = (char) (long int) a;
	char cb = (char) (long int) b;

	return( cb - ca );
}

//
// Process insertions/removals using a specific queue
//

static void process( QueueADT queue ) {
	long int i;

	fputs( "Inserting: ", stdout );
	for( i = 0; i < numData; ++i ) {
		printf( " '%c'", testData[i] );
		que_insert( queue, (void *) (long int) testData[i] );
	}

	fputs( "\nRemoving:  ", stdout );
	while( !que_empty(queue) ) {
		i = (char) (long int) que_remove( queue );
		printf( " '%c'", (char) i );
	}

	putchar( '\n' );
}


int main( void ) {
	QueueADT up, down, fifo;

	up = que_create( cmp_int64_ascend );
	if( up == NULL ) {
		fputs( "Cannot create ascending queue\n", stderr );
		exit( EXIT_FAILURE );
	}

	down = que_create( cmp_int64_descend );
	if( down == NULL ) {
		fputs( "Cannot create descending queue\n", stderr );
		exit( EXIT_FAILURE );
	}

	fifo = que_create( NULL );
	if( fifo == NULL ) {
		fputs( "Cannot create FIFO queue\n", stderr );
		exit( EXIT_FAILURE );
	}

	puts( "Testing the ascending queue" );
	process( up );

	puts( "\nTesting the descending queue" );
	process( down );

	puts( "\nTesting the FIFO queue" );
	process( fifo );

	que_destroy( up );
	que_destroy( down );
	que_destroy( fifo );

	return( 0 );
}

