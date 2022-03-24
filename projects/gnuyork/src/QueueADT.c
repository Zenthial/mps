/// QueueADT implementation file
/// description: implements the full ADT methods defined in QueueADT.h
/// also contains helper functions to sort and to create linked list nodes
/// provides all necessary queue functionality
/// user: tss2344
/// author: Tom Schollenberger

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/// the type definition of the comparison function
/// takes two void pointers, which are the pointers to be compared
typedef int (*cmp)(const void * a, const void * b);

/**
 * @brief internal definition of a node within the queue
 * val is a void pointer to any 64 bit value that the node contains
 * next is the node before it, while previous is the node after it.
 * its a bit confusing, appologies
 */
typedef struct queueNode {
    void *val;
    struct queueNode *next;
    struct queueNode *previous;
} QueueNode;

/**
 * @brief internal definition of the Queue
 * has a pointer to both the first and last node within the queue
 * tracks the number of nodes in the queue
 * has an optional comparison function pointer
 */
typedef struct queueADT {
    QueueNode *first;
    QueueNode *last;
    int numNodes;
    cmp comparison;
} * QueueADT;

#define _QUEUE_IMPL_
#include "QueueADT.h"


// creates a queue, with an optional comparison function
QueueADT que_create(int (*cmp)(const void * a, const void * b)) {
    QueueADT queue = (QueueADT)malloc(sizeof(struct queueADT));
    queue->first = NULL;
    queue->last = NULL;
    queue->numNodes = 0;
    queue->comparison = NULL;
    if (cmp != NULL) {
        queue->comparison = cmp;
    }

    return queue;
}

// clears a queue without freeing the queue itself
void que_clear(QueueADT queue) {
    if (queue->numNodes > 0) {
        QueueNode *next = queue->first;
        while (next != NULL) {
            QueueNode *temp = next->previous;

            free(next);
            next = temp;
        }
    }

    queue->comparison = NULL;
    queue->numNodes = 0;
}

// simply clears the nodes inside the queue then frees the queue pointer
void que_destroy(QueueADT queue) {
    que_clear(queue);

    free(queue);
}

/**
 * @brief Swaps two node's values in a linked list
 * 
 * @param a The first node to swap
 * @param b The second node to swap
 */
void swap(QueueNode *a, QueueNode *b) {
    void *temp = a->val;
    a->val = b->val;
    b->val = temp;
}

/**
 * @brief sorts a linked list
 * 
 * @param head The head node of a linked list
 * @param comparison The comparsion function to sort with
 */
void sort(QueueNode *head, cmp comparison) {
    bool swapped = false;

    if (head == NULL)
        return;
  
    do {
        swapped = false;
        QueueNode *pointer = head;
  
        while (pointer != NULL && pointer->previous != NULL) {
            if (comparison(pointer->val, pointer->previous->val) > 0) { 
                swap(pointer, pointer->previous);
                swapped = true;
            }

            pointer = pointer->previous;
        }
    }
    while (swapped);
}

/**
 * @brief Creates a node object
 * 
 * @param data pointer to the data the node should hold
 * @return QueueNode* 
 */
QueueNode *create_node(void * data) {
    QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
    node->val = data;
    node->next = NULL;
    node->previous = NULL;

    return(node);
}

// inserts a node into the queue
void que_insert(QueueADT queue, void * data) {
    QueueNode *nodeToAdd = create_node(data);

    // this ensures that queue->first also is not NULL
    // if it was NULL, then last would have to be NULL
    // if last isn't NULL, that means there is at least one value in the queue
    if (queue->last == NULL) {
        queue->last = nodeToAdd;
        queue->first = nodeToAdd;
        queue->numNodes++;
        return;
    }

    QueueNode *oldFirst = queue->first;
    oldFirst->next = nodeToAdd;
    nodeToAdd->previous = oldFirst;
    queue->first = nodeToAdd;

    queue->numNodes++;

    if(queue->comparison != NULL) {
        sort(queue->first, queue->comparison);
    }
}

// removes the oldest node from the queue if no comparison function, else removes the first
void *que_remove(QueueADT queue) {
    assert(queue->numNodes != 0);
    if (queue->comparison == NULL) {
        QueueNode *last = queue->last;
        void *retVal = last->val;
        queue->last = last->next;
        if (queue->last != NULL) {
            queue->last->previous = NULL;
        }
        queue->numNodes--;
        free(last);

        return retVal;
    } else {
        QueueNode *first = queue->first;
        void *retVal = first->val;
        queue->first = first->previous;
        queue->numNodes--;
        if (first == queue->last) {
            queue->last = NULL;
        }
        free(first);

        return retVal;
    }
}

// checks if the queue is empty
bool que_empty(QueueADT queue) {
    return queue->numNodes == 0;
}
