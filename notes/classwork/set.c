#define DEFAULT_INT_ARRAY_SIZE 100

typedef int (*cmp)(void *one, void *two);

#define _SET_INCLUDE_
typedef struct set_ {
    int *arr;
    int size;
    int num_elements;
    cmp comparsion;
} Set;

#include "set.h"

Set *set_create(cmp comparsion) {
    Set *return_set = (Set *)malloc(sizeof(Set));
    return_set->arr = (int *)malloc(sizeof(int) * DEFAULT_INT_ARRAY_SIZE);
    return_set->size = DEFAULT_INT_ARRAY_SIZE;
    return_set->num_elements = 0;
    return_set->comparsion = comparsion;

    return return_set;
}

int hash_code(void *value, int size) {
    return (int)value % size;
}

int find_open(int hash_code, int *arr, int size) {
    if (arr[hash_code] == 0)
        return hash_code;
    else {
        while (arr[hash_code] != 0) {
            hash_code++;
            if (hash_code >= size) {
                hash_code = 0;
            }
        }

        return hash_code;
    }
}

int find_value(int hash_code, int *arr, int size, void *val) {
    if (arr[hash_code] == val)
        return hash_code;
    else {
        while (arr[hash_code] != val) {
            hash_code++;
            if (hash_code >= size) {
                hash_code = 0;
            }
        }

        return hash_code;
    }
}

void set_add(Set *set, void *value) {
    int index = find_open(hash_code(value, set->size), set->arr, set->size);
    set->arr[index] = value;
}

void set_remove(Set *set, void *value) {
    int index = find_value(hash_code(value, set->size), set->arr, set->size, value);

}