#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <object_list.h> 
#include "simple_graph.h"

GraphNode * grh_create_node( char * name ) {
    ObjectList *neighbors = ol_create();
    GraphNode *node = (GraphNode *)malloc(sizeof(GraphNode));
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
    free(iter);
}

GraphNode * grh_find_node_by_name( ObjectList * graph, char * name ) {
    Iter *iter = ol_iterator(graph);
    while (ol_has_next(iter)) {
        GraphNode *node = (GraphNode *)ol_next(iter);
        if (strcmp(node->name, name) == 0) {
            free(iter);
            return node;
        }
    }

    free(iter);
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

    free(iter);
}

void grh_print_graph( ObjectList * graph ) {
    if (ol_get_size(graph) <= 0) {
        return;
    }
    
    printf("Graph: {name: neighbor names list}\n");
    Iter *iter = ol_iterator(graph);

    while (ol_has_next(iter)) {
        GraphNode *node = (GraphNode *)ol_next(iter);
        grh_print_node(node);
    }

    free(iter);
}

void grh_load_file( ObjectList * graph, FILE * input ) {
    char buff[MAX_FILE_LINE_LENGTH + 1];
    const char delim[] = ",";

    while (1) {
        char *result = fgets(buff, MAX_FILE_LINE_LENGTH, input);

        if ( result == NULL ) {            // check for input error

            if ( ! feof( stdin ) ) {       // if not end of file
                printf( "input error\n" );
            }
            
            break;                         // bail out of read loop

        } else {

            // chop off newline if is it also newline-terminated.
            if ( buff[strlen(buff)-1] == '\n' ) buff[strlen(buff)-1] = '\0';
        }

        if (strlen(buff) > 0) {
            char *start_node_name = strtok(buff, delim);

            GraphNode *start_node = grh_find_node_by_name(graph, start_node_name);

            if (start_node == NULL) {
                start_node = grh_create_node(start_node_name);

                ol_insert(graph, start_node);
            }

            char *neighbor = strtok(NULL, ",");
            while (neighbor != NULL) {
                GraphNode *neighbor_node = grh_find_node_by_name(graph, neighbor);
                if (neighbor_node == NULL) {
                    neighbor_node = grh_create_node(neighbor);
                    ol_insert(graph, neighbor_node);
                }

                if (grh_find_node_by_name(start_node->neighbors, neighbor) == NULL) {
                    ol_insert(start_node->neighbors, neighbor_node);
                }

                if (grh_find_node_by_name(neighbor_node->neighbors, start_node_name) == NULL) {
                    ol_insert(neighbor_node->neighbors, start_node);
                }

                neighbor = strtok(NULL, delim);
            }
        }
    }
}