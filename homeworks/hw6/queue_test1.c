// file: queue_test1.c
//
// Description:  test driver for the QueueADT module provided to students
//
// This test program creates three queues (one an ascending-ordered
// queue, one a descending-ordered queue, and one a FIFO queue),
// inserts a number of integer items into it, and then removes and
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

static long int testData[] = { 42, 17, -12, 9982, 476, 2912, -22, 3291213, 7782 };
static int numData = sizeof(testData) / sizeof(long int);

//
// Comparison function for integers sorted in ascending order
//

static int cmp_int64_ascend( const void *a, const void *b ) {
	long int na = (long int) a;
	long int nb = (long int) b;

	return( na - nb );
}

//
// Comparison function for integers sorted in descending order
//

static int cmp_int64_descend( const void *a, const void *b ) {
	long int na = (long int) a;
	long int nb = (long int) b;

	return( nb - na );
}

//
// Process insertions/removals using a specific queue
//

static void process( QueueADT queue ) {
	long int i;

	fputs( "Inserting: ", stdout );
	for( i = 0; i < numData; ++i ) {
		printf( " %ld", testData[i] );
		que_insert( queue, (void *) testData[i] );
	}

	fputs( "\nRemoving:  ", stdout );
	while( !que_empty(queue) ) {
		i = (long int) que_remove( queue );
		printf( " %ld", i );
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

