// File: tedtalktest.c 
// 
// Description: test the tedtalk.c module
// @author      RIT CS Instructors
// @author      Thomas Schollenberger
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

//
// Content supplied to the student.
//

#include <stdio.h>
#include <stdlib.h>

#include "tedtalk.h"
#include "EventTime.h"

/// main function tests the tedtalk module.
/// @returns error code or EXIT_SUCCESS if no error

int main( void ) {

    EventTime_t * atime = NULL ;
    TEDtalk_t * talk1 = NULL ;
    TEDtalk_t * talk2 = NULL ;
    TEDtalk_t * talk3 = NULL ;

    printf( "Creating a time...\n" ) ;
    // THIS POINTER IS FREED WHEN TALK1 IS DELETED
    atime = new_event_time( 6, 30, "pm" ) ;

    printf( "Starting tedtalk tests...\n" ) ;

    talk1 = new_TEDtalk( "Do schools kill creativity?", "Ken Robinson" ) ;
    printf( "First tedtalk initialized...\n" ) ;

    char * speaker = tedtalk_get_speaker( talk1 ) ;
    char * title = tedtalk_get_title( talk1 ) ;
    printf( "The current tedtalk is: \n\t%s by %s.\n", title, speaker) ;
    free( speaker ) ;
    free( title ) ;

    // WARNING: THIS POINTER IS REDEFINED MULTIPLE TIMES
    // BEFORE DEFINING IT AGAIN, MAKE SURE IT IS FREED TO AVOID MEM LEAKS
    char * mstr = tedtalk_to_string( talk1 ) ;
    printf( "Otherwise... %s\n", mstr ) ;
    free( mstr ) ;

    // atime gets added into the talk1 struct here, so it is cleaned up when talk1 is deleted
    tedtalk_play( talk1, atime ) ;
    mstr = tedtalk_to_string(talk1);
    printf( "After playing the tedtalk... \n\t%s\n", mstr ) ;
    free( mstr ) ;

    EventTime_t * glp = tedtalk_get_last_played( talk1 ) ;
    char * sglp = time_to_string(glp) ;
    speaker = tedtalk_get_speaker( talk1 ) ;
    title = tedtalk_get_title( talk1 ) ;
    printf( "The same tedtalk referencing members is: \n\t%s by %s. Last played at: %s\n", 
             title, speaker, sglp ) ;
    free( speaker ) ;
    free( title ) ;
    time_delete( glp ) ;
    free( sglp ) ;

    tedtalk_delete( talk1 ) ; // frees atime here

    speaker = malloc( sizeof( "Amy Cuddy" ) + 1 ) ;
    title = malloc( sizeof( "Your body shapes who you are" ) + 1 ) ;
    strcpy( speaker, "Amy Cuddy" ) ;
    strcpy( title, "Your body shapes who you are" ) ;
    talk2 = new_TEDtalk( title, speaker ) ;
    free( speaker ) ;
    free( title ) ;
    mstr = tedtalk_to_string( talk2 ) ;
    printf( "The talk2 is: \n\t%s\n", mstr ) ;
    free( mstr ) ;
    
    talk1 = tedtalk_copy( talk2 ) ;
    mstr = tedtalk_to_string( talk1 ) ;
    printf( "The copy of talk2 tedtalk is: \n\t%s \n", mstr ) ;
    free( mstr ) ;
    tedtalk_delete(talk2);
    mstr = tedtalk_to_string( talk1 ) ;
    printf( "After deleting the original talk2, the copy of talk2 "
            "tedtalk is ... \n\t%s\n", mstr ) ;
    free( mstr ) ; // avoid mem leaks

    char * pstr ;
    talk3 = tedtalk_copy( talk1 ) ;
    if ( tedtalk_equals( talk1, talk3 ) ) {
        mstr = tedtalk_to_string(talk1);
        pstr = tedtalk_to_string( talk3 ) ;
        printf( "The talk3 tedtalk \n\t%s\n"
                "    is the same as this tedtalk \n\t%s\n", pstr, mstr ) ;
        free( pstr ) ;
        free( mstr ) ; // avoid mem leaks
    }
    else {
        printf( "ERROR: tedtalk_copy() failure!\n" ) ;
    }

    tedtalk_delete( talk3 ) ;
    tedtalk_delete( talk1 ) ;

    talk3 = new_TEDtalk( "How great leaders inspire action", "Simon Sinek" ) ;
    mstr = tedtalk_to_string( talk3 ) ;
    printf( "The current talk3 tedtalk is: \n\t%s\n", mstr ) ;
    free( mstr ) ;
    
    tedtalk_play(talk3, new_event_time(4, 42, "am"));

    mstr = tedtalk_to_string( talk3 ) ;
    printf( "The current talk3 tedtalk is: \n\t%s\n", mstr ) ;
    free( mstr ) ;

    // tedtalk_delete( talk1 ) ;
    tedtalk_delete( talk3 ) ;

    return EXIT_SUCCESS ;
}
