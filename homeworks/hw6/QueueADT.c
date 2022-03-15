/// QueueADT implementation file
/// description: implements the full ADT methods defined in QueueADT.h
/// provides all necessary queue functionality
/// user: tss2344
/// author: Tom Schollenberger

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "QueueADT.h"

typedef int (*cmp)(const void * a, const void * b);

typedef struct queueNode {
    void *val;
    struct queueNode *next;
    struct queueNode *previous;
} QueueNode;

typedef struct queueADT {
    QueueNode *first;
    QueueNode *last;
    int numNodes;
    cmp comparison;
} QueueADT_T;

QueueADT que_create( int (*cmp)(const void * a, const void * b) ) {
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

void que_destroy( QueueADT queue ) {
    QueueADT_T *qADT = (QueueADT_T *)queue;
    if (qADT->numNodes > 0) {
        QueueNode *next = qADT->first;
        while (next != NULL) {
            QueueNode *temp = next->previous;
            free(next);
            next = temp;
        }
    }
    
    free(qADT);
}

void que_clear( QueueADT queue ) {
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

void swap(QueueNode *a, QueueNode *b) {
    void *temp = a->val;
    a->val = b->val;
    b->val = temp;
}

void bubbleSort(QueueNode *head, cmp comparison) {
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

QueueNode *create_node(void * data) {
    QueueNode *node = (QueueNode *) malloc(sizeof(QueueNode));
    node->val = data;
    node->next = NULL;
    node->previous = NULL;

    return(node);
}

void que_insert( QueueADT queue, void * data ) {
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
        bubbleSort(qADT->first, qADT->comparison);
    }
}

void *que_remove( QueueADT queue ) {
    QueueADT_T *qADT = (QueueADT_T *)queue;
    // printf("num left: %d\n", qADT->numNodes);
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

bool que_empty( QueueADT queue ) {
    QueueADT_T *qADT = (QueueADT_T *)queue;
    return qADT->numNodes == 0;
}