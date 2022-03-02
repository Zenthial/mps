#include <stdio.h>
#include <stdlib.h>

#include <object_list.h> 
#include "simple_graph.h"

int main( void ) {
    ObjectList *graph = ol_create();
    printf("Reading graph data...\n");
    grh_load_file(graph, stdin);
    printf("Finished reading graph data.\nGraph: {name: neighbor names list}\n");
    grh_print_graph(graph);
    grh_delete_graph(graph);

    return EXIT_SUCCESS;
}