// File:         tedtalk.h
// Description:  Interface for a module that represents a TEDtalk
// @author:      RIT CS Instructors
//

#ifndef TEDTALK_H
#define TEDTALK_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "EventTime.h"

/// The TEDtalk_t structure represents a TED talk that may be streamed.

typedef struct TEDtalk TEDtalk_t;

/// Create a TEDtalk_t structure with the supplied arguments and
/// set the time last played to NULL.
/// @param title string name of the talk
/// @param creator string name of the creator/presenter

TEDtalk_t * new_TEDtalk( char * title, char * creator);

/// delete the instance
/// @param item pointer to the talk to delete

void tedtalk_delete( TEDtalk_t * item);

/// @param item pointer to the talk
/// @param other pointer to the other talk to compare to item
/// @return non-zero(true) iff speaker and title are equivalent

bool tedtalk_equals( const TEDtalk_t * item, const TEDtalk_t * other );

/// @param item pointer to the talk
/// @return pointer to a copy of the talk

TEDtalk_t * tedtalk_copy( const TEDtalk_t * item);

/// @param item pointer to the talk
/// @return a c string pointer to the speaker/author of the talk

char * tedtalk_get_speaker( const TEDtalk_t * item);

/// @param item pointer to the talk
/// @return pointer to title of the talk as a c string

char * tedtalk_get_title( const TEDtalk_t * item);

/// record the last time tedtalk played (NULL if never)
/// @param item pointer to the talk
/// @param pointer to time of the streaming event

void tedtalk_play( TEDtalk_t * item, EventTime_t * time);

/// @param item pointer to the talk
/// @return pointer to the streaming event time, if any; otherwise NULL.

EventTime_t * tedtalk_get_last_played( const TEDtalk_t * item);

/// @param item pointer to the talk
/// @return pointer to c string representation of the item

char * tedtalk_to_string( const TEDtalk_t * item);

#endif