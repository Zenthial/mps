/// QueueADT implementation file
/// description: implements the full ADT methods defined in QueueADT.h
/// also contains helper functions to sort and to create linked list nodes
/// provides all necessary queue functionality
/// user: tss2344
/// author: Tom Schollenberger

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "QueueADT.h"

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
} QueueADT_T;

// creates a queue, with an optional comparison function
QueueADT que_create(int (*cmp)(const void * a, const void * b)) {
    QueueADT_T *queue = (QueueADT_T *)malloc(sizeof(struct queueADT));
    queue->first = NULL;
    queue->last = NULL;
    queue->numNodes = 0;
    queue->comparison = NULL;
    if (cmp != NULL) {
        queue->comparison = cmp;
    }

    return (QueueADT)queue;
}

// clears a queue without freeing the queue itself
void que_clear(QueueADT queue) {
    QueueADT_T *qADT = (QueueADT_T *)queue;
    if (qADT->numNodes > 0) {
        QueueNode *next = qADT->first;
        while (next != NULL) {
            QueueNode *temp = next->previous;
            free(next);
            next = temp;
        }
    }

    qADT->comparison = NULL;
    qADT->numNodes = 0;
}

// simply clears the nodes inside the queue then frees the queue pointer
void que_destroy(QueueADT queue) {
    QueueADT_T *qADT = (QueueADT_T *)queue;
    que_clear(queue);

    free(qADT);
}

QueueNode *getTail(QueueNode *cur) {
    while (cur != NULL && cur->previous != NULL) {
        cur = cur->previous;
    }

    return cur;
}
  

QueueNode *partition(QueueNode *head, QueueNode *end, QueueNode **newHead, QueueNode **newEnd, cmp comparison) {
    QueueNode *pivot = end;
    QueueNode *prev = NULL, *cur = head, *tail = pivot;
  
    while (cur != pivot) {
        if (comparison(cur->val, pivot->val) < 0) {
            if (*newHead == NULL) {
               *newHead = cur;
            }

            prev = cur;
            cur = cur->previous;
        } else {

            if (prev) {
                prev->previous = cur->previous;
            }

            QueueNode *tmp = cur->previous;
            cur->previous = NULL;
            tail->previous = cur;
            tail = cur;
            cur = tmp;
        }
    }
  
    if (*newHead == NULL) {
        *newHead = pivot;
    }

    *newEnd = tail;
  
    return pivot;
}
  

QueueNode *sort_recursion(QueueNode *head, QueueNode *end, cmp comparison) {
    // Base condition
    if (!head || head == end)
        return head;
  
    QueueNode *newHead = NULL, *newEnd = NULL;
  

    QueueNode *pivot = partition(head, end, &newHead, &newEnd, comparison);
    if (newHead != pivot) {

        QueueNode *tmp = newHead;
        while (tmp->previous != pivot)
            tmp = tmp->previous;
        tmp->previous = NULL;
  

        newHead = sort_recursion(newHead, tmp, comparison);
  
        tmp = getTail(newHead);
        tmp->previous = pivot;
    }

    pivot->previous = sort_recursion(pivot->previous, newEnd, comparison);
  
    return newHead;
}
  
QueueNode *quick_sort(QueueNode *head, cmp comparison) {
    return sort_recursion(head, getTail(head), comparison);
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
    QueueADT_T *qADT = (QueueADT_T *)queue;
    QueueNode *nodeToAdd = create_node(data);

    // this ensures that qADT->first also is not NULL
    // if it was NULL, then last would have to be NULL
    // if last isn't NULL, that means there is at least one value in the queue
    if (qADT->last == NULL) {
        qADT->last = nodeToAdd;
        qADT->first = nodeToAdd;
        qADT->numNodes++;
        return;
    }

    QueueNode *oldFirst = qADT->first;
    oldFirst->next = nodeToAdd;
    nodeToAdd->previous = oldFirst;
    qADT->first = nodeToAdd;

    qADT->numNodes++;

    if(qADT->comparison != NULL) {
        qADT->first = quick_sort(qADT->first, qADT->comparison);
    }
}

// removes the oldest node from the queue if no comparison function, else removes the first
void *que_remove(QueueADT queue) {
    QueueADT_T *qADT = (QueueADT_T *)queue;

    assert(qADT->numNodes != 0);
    if (qADT->comparison == NULL) {
        QueueNode *last = qADT->last;
        void *retVal = last->val;
        qADT->last = last->next;
        qADT->numNodes--;
        free(last);

        return retVal;
    } else {
        QueueNode *first = qADT->first;
        void *retVal = first->val;
        qADT->first = first->previous;
        qADT->numNodes--;
        free(first);

        return retVal;
    }
}

// checks if the queue is empty
bool que_empty(QueueADT queue) {
    QueueADT_T *qADT = (QueueADT_T *)queue;
    return qADT->numNodes == 0;
}