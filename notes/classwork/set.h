#include <stdbool.h>

#ifndef _SET_H_
#define _SET_H_

#ifndef _SET_INCLUDE_
#define _SET_INCLUDE_
typedef struct set_ Set;
#endif

/// creates a new set, returns a set pointer, requires a comparison function to determine if two values are equal
Set *set_create(int (*cmp)(void *one, void *two));

/// adds a value into the underlying set array 
/// any pointer that is added to the set must not be freed before being removed from the set
void set_add(Set *set, const void *value);

/// removes a value from the underlying set
void set_remove(Set *set, const void *value);

/// returns a newly allocated set
/// does not free either passed set
Set *set_union(const Set *one, const Set *two);

/// returns a newly intersected set
/// does not free either passed set
Set *set_intersection(const Set *one, const Set *two);

/// checks if a set contains a value, does not 
bool set_contains(const Set *set, const void *value);

#endif