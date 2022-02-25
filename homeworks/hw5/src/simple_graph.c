#include <string.h>
#include <stdio.h>

#include "simple_graph.h"

GraphNode * grh_create_node( char * name ) {
    ObjectList *neighbors = ol_create();
    GraphNode *node = malloc(MAX_NAME * sizeof(char) + sizeof(ObjectList));
    node->neighbors = neighbors;
    strncpy(node->name, name, sizeof(node->name));

    return node;
}

void grh_delete_node( GraphNode * node ) {
    // shouldnt need to cleanup each node in the neighbors because they'll all naturally be cleaned
    // as the entire graph is destroyed

    ol_destroy(node->neighbors);

    free(node);
}

void grh_delete_graph( ObjectList * graph ) {
    Iter *iter = ol_iterator(graph);
    while (ol_has_next(iter)) {
        GraphNode *node = (GraphNode *)ol_next(iter);
        grh_delete_node(node);
    }

    ol_destroy(graph);
}

GraphNode * grh_find_node_by_name( ObjectList * graph, char * name ) {
    Iter *iter = ol_iterator(graph);
    while (ol_has_next(iter)) {
        GraphNode *node = (GraphNode *)ol_next(iter);
        if (node->name == name) {
            return node;
        }
    }

    return NULL;
}

// private helper function for printing the graph
void grh_print_node(GraphNode *node) {
    Iter *iter = ol_iterator(node->neighbors);

    printf("%s: ", node->name);
    while (ol_has_next(iter)) {
        GraphNode *neighbor_node = (GraphNode *)ol_next(iter);
        printf("%s", neighbor_node->name);

        if (ol_has_next(iter)) {
            printf(", ");
        }
    }
    printf("\n");
}

void grh_print_graph( ObjectList * graph ) {
    Iter *iter = ol_iterator(graph);

    while (ol_has_next(iter)) {
        GraphNode *node = (GraphNode *)ol_next(iter);
        grh_print_node(node);
    }
}

void grh_load_file( ObjectList * graph, FILE * input );