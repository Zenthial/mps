/// QueueADT implementation file
/// author: Tom Schollenberger

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "QueueADT.h"

typedef int (*cmp)(const void * a, const void * b);

struct queueNode {
    void *val;
    struct queueNode *prev;
    struct queueNode *next;
};

struct queueADT {
    struct queueNode *newest;
    struct queueNode *oldest;
    int numNodes;
    cmp comparison;
};

QueueADT que_create( int (*cmp)(const void * a, const void * b) ) {
    struct queueADT *queue = (struct queueADT *)malloc(sizeof(struct queueADT));
    queue->newest = NULL;
    queue->oldest = NULL;
    queue->numNodes = 0;
    queue->comparison = NULL;
    if (cmp != NULL) {
        queue->comparison = cmp;
    }

    return (QueueADT)queue;
}

void que_destroy( QueueADT queue ) {
    struct queueADT *qADT = (struct queueADT *)queue;
    struct queueNode *next = qADT->oldest;
    while (next != NULL) {
        struct queueNode *temp = next->next;
        free(next);
        next = temp;
    }

    free(qADT);
}

void que_clear( QueueADT queue ) {
    struct queueADT *qADT = (struct queueADT *)queue;
    struct queueNode *next = qADT->oldest;
    while (next != NULL) {
        struct queueNode *temp = next->next;
        free(next);
        next = temp;
    }

    qADT->numNodes = 0;
}

struct queueNode *create_node(void * data, struct queueNode * prevNode) {
    struct queueNode *node = (struct queueNode *) malloc(sizeof(struct queueNode));
    node->val = data;
    node->prev = prevNode;
    node->next = NULL;

    return(node);
}

void que_insert( QueueADT queue, void * data ) {
    struct queueADT *qADT = (struct queueADT *)queue;
    struct queueNode *node = create_node(data, qADT->newest);
    if (qADT->comparison == NULL || (qADT->newest == NULL && qADT->comparison != NULL)) {
        qADT->newest->next = node;
        qADT->newest = node;
        qADT->numNodes++;
    } else {
        struct queueNode *prev = NULL;
        struct queueNode *current = qADT->newest;
        bool found = false;
        while (current != NULL) {
            struct queueNode *next = current->next;
            int result = qADT->comparison(current->val, node->val);
            if (result < 0) {
                current->next = node;
                next->prev = node;

                found = true;
                break;
            } else {
                current = next;
                prev = current;
            }

        }

        if (found == false) {
            qADT->oldest = node;
            node->prev = prev;
        }
    }
}

void *que_remove( QueueADT queue ) {
    struct queueADT *qADT = (struct queueADT *)queue;
    assert(qADT->numNodes == 0);
    struct queueNode *oldest = qADT->oldest;
    void *retVal = oldest->val;
    qADT->oldest = oldest->next;
    free(oldest);
    return(retVal);
}

bool que_empty( QueueADT queue ) {
    struct queueADT *qADT = (struct queueADT *)queue;
    return(qADT->numNodes == 0);
}