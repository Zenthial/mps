// file: build_graph.c
// description: 
// makes calls to load, print and destroy the graph
// author: tom schollenberger

#include <stdio.h>
#include <stdlib.h>

#include <object_list.h> 
#include "simple_graph.h"

// entry point of the program
int main( void ) {
    ObjectList *graph = ol_create();
    printf("Reading graph data...\n");
    grh_load_file(graph, stdin);
    printf("Finished reading graph data.\n");
    grh_print_graph(graph);
    grh_delete_graph(graph);

    return EXIT_SUCCESS;
}
