// file: queue_test3.c
//
// Description:  test driver for the QueueADT module provided to students
//
// This test program creates three queues (one an ascending-ordered
// queue, one a descending-ordered queue, and one a FIFO queue),
// inserts a number of ###c strings### into it, and then removes and
// prints them.
//
// Author:  wrc
// Author:  CS@RIT.EDU

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "QueueADT.h"

//
// Sequence of test values to be inserted and removed
//

static char *testData[] = { 
	  "Grendel this monster grim was called"
	, "Grendel's attack with terror of blades"
	, "Grendel in grimmest grasp thou killedst,"
	, "Grendel in days long gone they named him"
	, "Grendel to guerdon for grim raids many"
	, "Grendel stretched there, spent with war"
	, "Grendel's head, where the henchmen were drinking"
};

static int numData = sizeof(testData) / sizeof(char *);

//
// Comparison function for c strings sorted in ascending order
//

static int cmp_cstring_ascend( const void *a, const void *b ) {
	char * cpa = (char *) a;
	char * cpb = (char *) b;

	int collation = strcmp( cpa, cpb );
	return collation ;
}

//
// Comparison function for c strings sorted in descending order
//

static int cmp_cstring_descend( const void *a, const void *b ) {
	char *cpa = (char *) a;
	char *cpb = (char *) b;

	int collation = strcmp( cpa, cpb );
	return 0 - collation ;
}

//
// Process insertions/removals using a specific queue
//

static void process( QueueADT queue ) {
	int i;
	void *tmp;

	fputs( "Inserting: \n", stdout );
	for( i = 0; i < numData; ++i ) {
		printf( "%s\n", testData[i] );
		que_insert( queue, (void *) testData[i] );
	}

	fputs( "\nRemoving: \n", stdout );
	while( ! que_empty(queue) ) {
		tmp = (char *) que_remove( queue );
		printf( "%s\n", (char *)tmp );
	}

	putchar( '\n' );
}


int main( void ) {
	QueueADT up, down, fifo;

	up = que_create( cmp_cstring_ascend );
	if( up == NULL ) {
		fputs( "Cannot create ascending queue\n", stderr );
		exit( EXIT_FAILURE );
	}

	down = que_create( cmp_cstring_descend );
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

